// Font_CreationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Font_Creation.h"
#include "Font_CreationDlg.h"
#include <Windowsx.h>


/////////////////////////////////////////////
//Common File Dialog Helper
#define USE_FILE_DIALOG_DN(_ParentWnd,_FileNameFilter,_DefaultName) \
		TCHAR	_DFOD_Fn[MAX_PATH+1]; \
		_tcscpy(_DFOD_Fn,_DefaultName); \
		OPENFILENAME ofn; \
		ZeroMemory(&ofn,sizeof(ofn)); \
		ofn.lStructSize = sizeof(OPENFILENAME); \
		ofn.hwndOwner = _ParentWnd; \
		ofn.lpstrFilter = _FileNameFilter; \
		ofn.nFilterIndex = 1; \
		ofn.Flags = OFN_ENABLESIZING|OFN_OVERWRITEPROMPT|OFN_EXPLORER; \
		ofn.lpstrFile = _DFOD_Fn; \
		ofn.nMaxFile = MAX_PATH; \
		TCHAR _LastCurDir[MAX_PATH+1]; \
		LPTSTR _NameReturn; \
		VERIFY(::GetCurrentDirectoryW(MAX_PATH,_LastCurDir));

#define USE_FILE_DIALOG(_ParentWnd,_FileNameFilter)		USE_FILE_DIALOG_DN(_ParentWnd,_FileNameFilter,_T("\0"))
																
#define GET_FILENAME(_IsForRead)	((_NameReturn = ((LPTSTR)((_IsForRead?GetOpenFileName(&ofn):GetSaveFileName(&ofn))?_DFOD_Fn:NULL))),VERIFY(::SetCurrentDirectoryW(_LastCurDir)),_NameReturn)
#define APPEND_EXTNAME(PathName,FileExt) { LPTSTR _p_=_tcsrchr(PathName,_T('\\')); if(!_p_)_p_=PathName; if(!_tcsrchr(_p_,_T('.')))_tcscat(_p_,FileExt); }
#define REPLACE_EXTNAME(PathName,FileExt) { LPTSTR _p_=_tcsrchr(PathName,_T('\\')); if(!_p_)_p_=PathName; if(_p_=_tcsrchr(_p_,_T('.'))){_tcscpy(_p_,FileExt);}else{_tcscat(PathName,FileExt);} }
#define REMOVE_EXTNAME(PathName) { LPTSTR _p_=_tcsrchr(PathName,_T('\\')); if(!_p_)_p_=PathName; if(_p_=_tcsrchr(_p_,_T('.'))){*_p_=0;} }


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Gdiplus;

CFont_CreationDlg::CFont_CreationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFont_CreationDlg::IDD, pParent)
	, m_sInput(_T(""))
	, m_sFontSize(_T("16"))
	, m_sFontContrast(_T("100"))
	, m_FontCharSeed(0)
	, m_bShowGrid(false)
	, m_sFontWeight(_T(""))
	, m_FontHeight(20)
	, m_bInvert(false)
	, m_bOverallDisplay(false)
	, m_PixelFormat(2)
	, m_sTestText(_T(""))
	, m_GlyphLineWidthIndex(0)
	, m_bSwizzleMap(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_CodeMin = L'A';
	m_CodeMax = L'Z';
	m_IsFontListUpdated = false;
	m_CodeAreaCheckedCount = 0;
	m_SelectedCodeArea = 0;

	m_FontSize = 20;
}

void CFont_CreationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_sInput);
	DDX_Control(pDX, IDC_CODE_CHART, m_wChartTree);
	DDX_Control(pDX, IDC_CHART_INFO, m_wChartInfo);
	DDX_Control(pDX, IDC_FontList, m_wFontPicker);
	DDX_Control(pDX, IDC_FONTSIZE, m_wFontSize);
	DDX_Check(pDX, IDC_FONT_BOLD, m_FontBold);
	DDX_Check(pDX, IDC_FONT_BOLD2, m_FontItalic);
	DDX_Check(pDX, IDC_FONT_BOLD3, m_FontUnderline);
	DDX_Check(pDX, IDC_FONT_BOLD4, m_FontStrikeout);
	DDX_CBString(pDX, IDC_FONTSIZE, m_sFontSize);
	DDX_CBString(pDX, IDC_FONTSIZE2, m_sFontContrast);
	DDX_Control(pDX, IDC_FONTSIZE2, m_wFontContrast);
	DDX_Control(pDX, IDC_FONT_AA, m_wFontAA);
	DDX_Control(pDX, IDC_FONT_QUALITY, m_wFontQuality);
	DDX_Control(pDX, IDC_FONT_WEIGHT, m_wFontWeight);
	DDX_CBString(pDX, IDC_FONT_WEIGHT, m_sFontWeight);
	DDX_Control(pDX, IDC_GENE_INFO, m_wTotalInfo);
	DDX_Check(pDX, IDC_FONT_BOLD5, m_FixedWidth);
	DDX_Control(pDX, IDC_FONT_BOLD5, m_wFixedWidth);
	DDX_Text(pDX, IDC_EDIT3, m_Baseline);
	DDX_Text(pDX, IDC_EDIT4, m_WidthShrink);
	DDX_Text(pDX, IDC_EDIT5, m_LeftMargin);
	DDX_Text(pDX, IDC_EDIT2, m_FontHeight);
	DDX_Check(pDX, IDC_DISPLAY_INVERT, m_bInvert);
	DDX_Check(pDX, IDC_CHECK1, m_bOverallDisplay);
	DDX_Control(pDX, IDC_COMBO1, m_wPixelFormat);
	DDX_CBIndex(pDX, IDC_COMBO1, m_PixelFormat);
	DDX_Text(pDX, IDC_EDIT6, m_sTestText);
	DDX_CBIndex(pDX, IDC_ImageStep, m_GlyphLineWidthIndex);
	DDX_Control(pDX, IDC_ImageStep, m_wImageStep);
	DDX_Check(pDX, IDC_CHECK2, m_bSwizzleMap);
}

BEGIN_MESSAGE_MAP(CFont_CreationDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CFont_CreationDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CFont_CreationDlg::OnBnClickedButtonTest)
	ON_BN_CLICKED(IDC_BUTTON_TEST2, &CFont_CreationDlg::OnBnClickedButtonTest2)
	ON_NOTIFY(TVN_SELCHANGED, IDC_CODE_CHART, &CFont_CreationDlg::OnTvnSelchangedCodeChart)
	ON_NOTIFY(TVN_CHECKCHANGING, IDC_CODE_CHART, &CFont_CreationDlg::OnTvnCheckchangedCodeChart)
	ON_CBN_SELCHANGE(IDC_FontList, &CFont_CreationDlg::OnCbnSelchangeFontlist)
	ON_CBN_EDITCHANGE(IDC_FONTSIZE, &CFont_CreationDlg::OnCbnEditchangeFontsize)
	ON_BN_CLICKED(IDC_FONT_BOLD, &CFont_CreationDlg::OnBnClickedFontBold)
	ON_BN_CLICKED(IDC_FONT_BOLD2, &CFont_CreationDlg::OnBnClickedFontBold2)
	ON_BN_CLICKED(IDC_FONT_BOLD3, &CFont_CreationDlg::OnBnClickedFontBold3)
	ON_BN_CLICKED(IDC_FONT_BOLD4, &CFont_CreationDlg::OnBnClickedFontBold4)
	ON_CBN_SELCHANGE(IDC_FONTSIZE, &CFont_CreationDlg::OnCbnSelchangeFontsize)
	ON_CBN_SELCHANGE(IDC_FONTSIZE2, &CFont_CreationDlg::OnCbnSelchangeFontsize2)
	ON_CBN_EDITCHANGE(IDC_FONTSIZE2, &CFont_CreationDlg::OnCbnEditchangeFontsize2)
	ON_CBN_SELCHANGE(IDC_FONT_AA, &CFont_CreationDlg::OnCbnSelchangeFontAa)
	ON_CBN_SELCHANGE(IDC_FONT_QUALITY, &CFont_CreationDlg::OnCbnSelchangeFontQuality)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_CBN_SELCHANGE(IDC_FONT_WEIGHT, &CFont_CreationDlg::OnCbnSelchangeFontWeight)
	ON_CBN_EDITCHANGE(IDC_FONT_WEIGHT, &CFont_CreationDlg::OnCbnEditchangeFontWeight)
	ON_BN_CLICKED(IDC_BUTTON_COPY, &CFont_CreationDlg::OnBnClickedButtonCopy)
	ON_BN_CLICKED(IDC_BUTTON_PASTE, &CFont_CreationDlg::OnBnClickedButtonPaste)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CFont_CreationDlg::OnBnClickedButtonSave)
	ON_CBN_DROPDOWN(IDC_FontList, &CFont_CreationDlg::OnCbnDropdownFontlist)
	ON_BN_CLICKED(IDC_CHECK1, &CFont_CreationDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_FONT_BOLD5, &CFont_CreationDlg::OnBnClickedFontBold5)
	ON_EN_CHANGE(IDC_EDIT3, &CFont_CreationDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CFont_CreationDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CFont_CreationDlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT2, &CFont_CreationDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_DISPLAY_INVERT, &CFont_CreationDlg::OnBnClickedDisplayInvert)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CFont_CreationDlg::OnBnClickedButtonImport)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CFont_CreationDlg::OnBnClickedButtonExport)
	ON_BN_CLICKED(IDC_BUTTON_SAVE2, &CFont_CreationDlg::OnBnClickedButtonSave2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CFont_CreationDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE, &CFont_CreationDlg::OnBnClickedButtonGenerate)
	ON_BN_CLICKED(IDC_BUTTON_TEST_UFG, &CFont_CreationDlg::OnBnClickedButtonTestUfg)
	ON_EN_CHANGE(IDC_EDIT6, &CFont_CreationDlg::OnEnChangeTestText)
	ON_BN_CLICKED(IDC_BUTTON_IMG2ARRAY, &CFont_CreationDlg::OnBnClickedButtonImg2array)
	ON_BN_CLICKED(IDC_BUTTON_COPYCODE, &CFont_CreationDlg::OnBnClickedButtonCopycode)
END_MESSAGE_MAP()


// CFont_CreationDlg message handlers


BOOL CFont_CreationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, true);			// Set big icon
	SetIcon(m_hIcon, false);		// Set small icon

	m_FontImage.Create(659,-497,32);
	{
		Graphics	g(m_FontImage.GetDC());
		SolidBrush	bg(Color(255,255,255));
		g.FillRectangle(&bg,0,0,m_FontImage.GetWidth(),m_FontImage.GetHeight());
	}
	m_FontImage.ReleaseDC();

	m_wImageStep.AddString(L"512");
	m_wImageStep.AddString(L"1024");
	m_wImageStep.AddString(L"2048");
	m_wImageStep.AddString(L"4096");
	m_wImageStep.AddString(L"8192");
	m_wImageStep.SetCurSel(0);

	// Pixel Format
	m_wPixelFormat.AddString(L"1 BPP");
	m_wPixelFormat.AddString(L"2 BPP");
	m_wPixelFormat.AddString(L"4 BPP");
	m_wPixelFormat.AddString(L"8 BPP");
	m_wPixelFormat.SetCurSel(3);

	//Font list
	m_FontList.EnumerateFont();

	UpdateFontList(false);
	SelectFontList(L"Times");

	//Font size lisit
	m_wFontSize.AddString(L"6");	m_wFontSize.SetItemData(0,6);
	m_wFontSize.AddString(L"8");	m_wFontSize.SetItemData(1,8);
	m_wFontSize.AddString(L"16");	m_wFontSize.SetItemData(2,16);
	m_wFontSize.AddString(L"20");	m_wFontSize.SetItemData(3,20);
	m_wFontSize.AddString(L"24");	m_wFontSize.SetItemData(4,24);
	m_wFontSize.AddString(L"28");	m_wFontSize.SetItemData(5,28);
	m_wFontSize.AddString(L"32");	m_wFontSize.SetItemData(6,32);
	m_wFontSize.AddString(L"48");	m_wFontSize.SetItemData(7,48);
	m_wFontSize.AddString(L"72");	m_wFontSize.SetItemData(8,72);
	m_wFontSize.SetCurSel(3);

	//Font size lisit
	{	UINT id = 0;
		for(UINT i=100;i<950;i+=100)
		{	WCHAR tt[10];
			wsprintf(tt,L"%d",i);
			m_wFontWeight.AddString(tt);	m_wFontWeight.SetItemData(id++,i);
		}
		m_wFontWeight.SetCurSel(3);
	}

	//Font contrast
	{
		UINT id = 0;
		for(UINT i=10;i<=500;i+=5)
		{	WCHAR tt[5];
			wsprintf(tt,L"%d",i);
			m_wFontContrast.AddString(tt);	m_wFontContrast.SetItemData(id++,i);
		}
		m_wFontContrast.SetCurSel(m_wFontContrast.FindString(-1,L"100"));
	}

	//Font AA
	m_wFontAA.AddString(L"Default");
	m_wFontAA.AddString(L"SingleBit/Fit");
	m_wFontAA.AddString(L"SingleBit");
	m_wFontAA.AddString(L"AntiAlias/Fit");
	m_wFontAA.AddString(L"AntiAlias");
	m_wFontAA.AddString(L"ClearType");
	m_wFontAA.SetCurSel(3);

	//Font Quality
	m_wFontQuality.AddString(L"Invalid");
	m_wFontQuality.AddString(L"Default");
	m_wFontQuality.AddString(L"High Quality");
	m_wFontQuality.AddString(L"High Speed");
	m_wFontQuality.SetCurSel(2);

	//Initialize unicode code chart tree
	for(UINT i=0;i<UR_REGION_MAX;i++)
	{
		m_RegionEntry[i] = m_wChartTree.InsertItem(unicode::g_RegionNames[i]);
		m_wChartTree.SetItemData(m_RegionEntry[i],0x1000|i);
	}

	for(UINT i=0;i<UNICODE_CHART_SIZE;i++)
	{	TCHAR name_buf[256];
		_stprintf(name_buf,_T("%s [%d]"),g_UnicodeCharts[i].Name,g_UnicodeCharts[i].CodeEnd-g_UnicodeCharts[i].CodeStart+1);	
		m_CodeAreaEntry[i] = m_wChartTree.InsertItem(name_buf,m_RegionEntry[g_UnicodeCharts[i].Region]);
		m_wChartTree.SetItemData(m_CodeAreaEntry[i],i);
	}

	m_wChartTree.SortChildren(TVI_ROOT);
	for(UINT i=0;i<UR_REGION_MAX;i++)
		m_wChartTree.SortChildren(m_RegionEntry[i]);

	return true;  // return true  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFont_CreationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();

		RedrawPreviewImage();
	}
}

void CFont_CreationDlg::RedrawPreviewImage()
{
	CClientDC dc(this);
	m_FontImage.Draw(dc,6,275);
}


void CFont_CreationDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(point.x>6 && point.y>275 && point.x<6+m_FontImage.GetWidth() && point.y<275+m_FontImage.GetHeight())
	{
		m_FontCharSeed = ((UINT)time(NULL))^GetTickCount();
		RedrawPreivewText();
	}

	CDialog::OnLButtonDown(nFlags, point);
}



// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFont_CreationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFont_CreationDlg::OnBnClickedOk()
{
}

bool CFont_CreationDlg::SelectFontList(LPCWSTR facename)
{
	int id;
	id = m_wFontPicker.FindString(-1,facename);
	if(id>=0)
	{	
		m_wFontPicker.SetCurSel(id);
		return true;
	}

	return false;
}

void CFont_CreationDlg::UpdateFontList(bool filter_charset)
{
	WCHAR string[255];

	srand(0);
	for(UINT i=0;i<255;i++)
		string[i] = rand()%(m_CodeMax-m_CodeMin+1) + m_CodeMin;
	HDC img_dc = m_FontImage.GetDC();

	int sel=0;
	m_wFontPicker.ResetContent();
	for(UINT i=0;i<m_FontList.GetSize();i++)
	{
		if(filter_charset)
		{
			CFont gdi_font;
			gdi_font.CreateFont(m_FontSize,0,0,0,
								m_FontBold?800:400,m_FontItalic,
								m_FontUnderline,m_FontStrikeout,
								0x0,0x3,0x2,ANTIALIASED_QUALITY,0x22,m_FontList[i].FaceName);

			HFONT org_hfont = SelectFont(img_dc,gdi_font);
			DeleteFont(org_hfont);

			WORD  gi[255];
			DWORD recog = ::GetGlyphIndices(img_dc,string,255,gi,GGI_MARK_NONEXISTING_GLYPHS);

			UINT j=0;
			for(;j<255;j++)
				if(gi[j] != 0xffff)break;
			if(j==255)continue;
		}

		WCHAR font_info[200];
		if(m_FontList[i].FixedPitch)
		{
			wsprintf(font_info,L"%s (FIX)", m_FontList[i].FaceName);
		}
		else
		{
			wsprintf(font_info,L"%s", m_FontList[i].FaceName);
		}

		int id = m_wFontPicker.AddString(font_info);
		m_wFontPicker.SetItemData(id,i);
	}

	m_FontImage.ReleaseDC();
}

void CFont_CreationDlg::OnBnClickedButtonTest()
{
	Graphics	g(m_FontImage.GetDC());
	SolidBrush	bg(Color(255,255,255));
	g.FillRectangle(&bg,0,0,m_FontImage.GetWidth(),m_FontImage.GetHeight());

	Font		f(L"times new roman",16,FontStyleRegular,UnitPixel,NULL);
	
	g.SetTextRenderingHint(TextRenderingHintAntiAlias);
	//g.SetCompositingQuality(CompositingQualityHighQuality);
	g.SetCompositingQuality(CompositingQualityHighSpeed);
	g.SetTextContrast(100);

	SolidBrush	tx(Color(0,0,0));
	g.DrawString(L" العربية Hel 我的 웹문서 Поиск のページ Ελληνικά ",-1,&f,PointF(0,0),&tx);

	m_FontImage.ReleaseDC();
	
	RedrawPreviewImage();
}

void CFont_CreationDlg::OnBnClickedButtonTest2()
{
}

void CFont_CreationDlg::OnTvnCheckchangedCodeChart(NMHDR *pNMHDR, LRESULT *pResult)
{	
	m_CharacterCount = 0;
	m_CodeAreaCheckedCount = 0;
	for(UINT i=0;i<UNICODE_CHART_SIZE;i++)
	{
		if(m_wChartTree.GetCheck(m_CodeAreaEntry[i]))
		{
			m_CharacterCount += unicode::g_UnicodeCharts[i].CodeEnd - unicode::g_UnicodeCharts[i].CodeStart + 1;
			m_CodeAreaChecked[m_CodeAreaCheckedCount] = i;
			m_CodeAreaCheckedCount++;
		}
	}

	if(m_CharacterCount)
	{	
		WCHAR info[200];
		wsprintf(info,L"Glyph Library Generation (%d glyphes in %d charts)",m_CharacterCount,m_CodeAreaCheckedCount);
		m_wTotalInfo.SetWindowText(info);
		GetDlgItem(IDC_CHECK1)->EnableWindow(true);
	}
	else
	{
		m_wTotalInfo.SetWindowText(L"Glyph Library Generation");
		GetDlgItem(IDC_CHECK1)->EnableWindow(false);
	}

	*pResult = 0;
}

void CFont_CreationDlg::OnTvnSelchangedCodeChart(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	HTREEITEM cur = pNMTreeView->itemNew.hItem;
	if(cur)
	{
		UINT chart_id = (UINT)m_wChartTree.GetItemData(cur);
		if(chart_id<1000)
		{	
			m_SelectedCodeArea = chart_id;
			m_CodeMin = unicode::g_UnicodeCharts[chart_id].CodeStart;
			m_CodeMax = unicode::g_UnicodeCharts[chart_id].CodeEnd;

			WCHAR text[200];
			wsprintf(text,	L"%s@%s: Unicode[%04X:%04X](%d)",
							unicode::g_UnicodeCharts[chart_id].Name,
							unicode::g_RegionNames[unicode::g_UnicodeCharts[chart_id].Region],
							m_CodeMin,m_CodeMax,(m_CodeMax-m_CodeMin) );
			m_wChartInfo.SetWindowText(text);

			m_IsFontListUpdated = false;
			m_wFontPicker.ResetContent();
			if(m_CodeAreaFontInfo[m_SelectedCodeArea].IsAvailable())
			{	
				UINT fid = m_FontList.SearchFont(m_CodeAreaFontInfo[m_SelectedCodeArea].m_FaceName);
				if(fid == 0xffffffff)
				{
					WCHAR info[100];
					wsprintf(info,L"%s - (Font not available)",m_CodeAreaFontInfo[m_SelectedCodeArea].m_FaceName);
					m_wFontPicker.AddString(info);
				}
				else
				{
					m_FontSelected = fid;
					WCHAR font_info[200];
					if(m_FontList[m_FontSelected].FixedPitch)
					{
						wsprintf(font_info,L"%s (FIX)", m_FontList[m_FontSelected].FaceName);
					}
					else
					{
						wsprintf(font_info,L"%s", m_FontList[m_FontSelected].FaceName);
					}

					m_wFontPicker.AddString(font_info);
					m_wFontPicker.SetCurSel(0);
				}

				CopyFontInfo(m_CodeAreaFontInfo[m_SelectedCodeArea]);

				//Setup UI
			}
			else
			{
				m_FontSelected = m_FontList.SearchFont(L"Arial Unicode MS");
				m_FontSize=20;
				m_FontContrast=100;
				m_FontQuality=1;
				m_FontAntiAliasMode=4;
				m_FontBold=false;
				m_FontItalic=false;
				m_FontUnderline=false;
				m_FontStrikeout=false;
				m_Baseline = 0;
				m_WidthShrink = 0;
				m_LeftMargin = 0;
				m_FixedWidth = false;

				wcscpy(m_FaceName,L"Arial Unicode MS");
				m_wFontPicker.AddString(m_FaceName);
				m_wFontPicker.SetCurSel(0);
			}

			m_wFixedWidth.SetWindowText(m_FixedWidth?L"   Fixed Width:":L"    R-Margin:");

			SetupUI();
			RedrawPreivewText();
		}
		else 
		{	// group selected
		}
	}

	*pResult = 0;
}

void CFont_CreationDlg::SetupUI()
{	
	m_wFontContrast.EnableWindow(m_FontAntiAliasMode>1);

	m_sFontSize.Format(L"%d",m_FontSize);
	m_sFontContrast.Format(L"%d",m_FontContrast);
	UpdateData(false);

	m_wFontAA.SetCurSel(m_FontAntiAliasMode);
	m_wFontQuality.SetCurSel(m_FontQuality+1);

	((CButton*)GetDlgItem(IDC_FONT_BOLD))->SetCheck(m_FontBold?BST_CHECKED:BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_FONT_BOLD2))->SetCheck(m_FontItalic?BST_CHECKED:BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_FONT_BOLD3))->SetCheck(m_FontUnderline?BST_CHECKED:BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_FONT_BOLD4))->SetCheck(m_FontStrikeout?BST_CHECKED:BST_UNCHECKED);
}


void CFont_CreationDlg::RedrawPreivewText(void)
{
	HDC img_dc = m_FontImage.GetDC();
	Graphics	g(img_dc);
	SolidBrush	bg(Color(254,254,254));
	SolidBrush	tx(Color(1,1,1));
	Pen pen(Color(0,150,0),1);
	RectF layoutRect(0, 0, 0, 0);

	g.FillRectangle(&bg,0,0,m_FontImage.GetWidth(),m_FontImage.GetHeight());

	{
		LPCWSTR fontname = L"Tahoma";
		if(m_FontSelected<m_FontList.GetSize())
		{
			fontname = m_FontList[m_FontSelected].FaceName;
		}

		CFont gdi_font;
		gdi_font.CreateFont(m_FontSize,0,0,0,
							m_FontBold?800:400,m_FontItalic,
							m_FontUnderline,m_FontStrikeout,
							0x0,0x3,0x2,ANTIALIASED_QUALITY,0x22,fontname);

		HFONT org_hfont = SelectFont(img_dc,gdi_font);
		DeleteFont(org_hfont);

		Font f(img_dc,gdi_font);

		g.SetTextRenderingHint((TextRenderingHint)m_FontAntiAliasMode);
		g.SetCompositingQuality((CompositingQuality)m_FontQuality);
		g.SetTextContrast(100);
		g.SetSmoothingMode(SmoothingModeHighQuality);


		BYTE value_mapping[256];

		if(m_FontAntiAliasMode>2)
		{
			for(int i=0;i<256;i++)
				value_mapping[i] = (BYTE)(255.0*pow(i/255.0,m_FontContrast/100.00) + 0.5);
		}
		else
		{
			for(int i=0;i<255;i++)
				value_mapping[i] = i;
		}

		if(!m_bInvert)
		{
			for(int i=0;i<256;i++)
				value_mapping[i] = 255 - value_mapping[i];
		}

		if(m_PixelFormat==0) // 1BPP
		{
			for(int i=0;i<256;i++)
				value_mapping[i] = value_mapping[i]>127?255:0;
		}
		else if(m_PixelFormat==1) // 2BPP
		{
			for(int i=0;i<256;i++)
				value_mapping[i] = value_mapping[i]&0xc0 + 0x1f;
		}
		else if(m_PixelFormat==2) // 4BPP
		{
			for(int i=0;i<256;i++)
				value_mapping[i] = value_mapping[i]&0xf0 + 0x7;
		}

		srand(m_FontCharSeed);
		float max_w=0,min_w=1e9;

		for(int y=0;y<m_FontImage.GetHeight();)
		{	
			float line_h = 0;
			for(int x=0;x<m_FontImage.GetWidth();)
			{
				WCHAR ch;
				RectF boundRect;

				////////////////////////////////////////////////////////
				// get a random char that is available in selected font
				UINT err_count = 0;
				do
				{
					ch = rand()%(m_CodeMax-m_CodeMin+1) + m_CodeMin;
					if(err_count > 255)
					{
						g.DrawString(L"This unicode range is not supportted in this font",-1,&f,PointF(0,0),&tx);
						m_FontImage.ReleaseDC();
						RedrawPreviewImage();
						return;
					}

					WORD  gi;
					::GetGlyphIndices(img_dc,&ch,1,&gi,GGI_MARK_NONEXISTING_GLYPHS);
					if(gi!=0xffff)
						g.MeasureString(&ch,1,&f,layoutRect,&boundRect);
					else
						boundRect.Width = 0.0f;

					err_count++;
				}
				while(boundRect.Width < 0.1f || boundRect.Height < 0.1f);

				boundRect.Height = (float)m_FontHeight;
				if(m_FixedWidth)
				{
					boundRect.Width = (float)m_WidthShrink;
				}
				else
				{
					boundRect.Width = floor(rt::max(2.0f,boundRect.Width-(m_LeftMargin+m_WidthShrink)) + 0.5f);
				}

				boundRect.Offset((float)x,(float)y);
				if(m_bShowGrid)g.DrawRectangle(&pen,boundRect);

				boundRect.X -= m_LeftMargin;
				boundRect.Y -= m_Baseline;

				g.DrawString(&ch,1,&f,PointF(boundRect.X,boundRect.Y),&tx);

				x += (UINT)boundRect.Width;
				max_w = rt::max(boundRect.Width,max_w);
				min_w = rt::min(boundRect.Width,min_w);

			}
			y+=m_FontHeight;
		}

		//post-process
		LPBYTE p = (LPBYTE)m_FontImage.GetBits();
		LPBYTE end = &p[m_FontImage.GetPitch()*m_FontImage.GetHeight()];
		for(;p<end;p++)*p = value_mapping[*p];

	}

	
	m_FontImage.ReleaseDC();
	RedrawPreviewImage();
}

void CFont_CreationDlg::OnCbnSelchangeFontlist()
{
	int sel = m_wFontPicker.GetCurSel();
	if(sel>=0)
	{
		UINT fid = (UINT)m_wFontPicker.GetItemData(sel);

		m_FontSelected = fid;
		memcpy(m_FaceName,m_FontList[fid].FaceName,sizeof(m_FaceName));
		RedrawPreivewText();
	}
}

void CFont_CreationDlg::OnBnClickedFontBold()
{
	UpdateData();
	RedrawPreivewText();
}

void CFont_CreationDlg::OnBnClickedFontBold2()
{
	UpdateData();
	RedrawPreivewText();
}

void CFont_CreationDlg::OnBnClickedFontBold3()
{
	UpdateData();
	RedrawPreivewText();
}

void CFont_CreationDlg::OnBnClickedFontBold4()
{
	UpdateData();
	RedrawPreivewText();
}

void CFont_CreationDlg::OnCbnSelchangeFontsize()
{
	int cursel = m_wFontSize.GetCurSel();
	m_FontSize = (int)m_wFontSize.GetItemData(cursel);
	RedrawPreivewText();
}

void CFont_CreationDlg::OnCbnEditchangeFontsize()
{
	UpdateData();
	m_FontSize = rt::max(8,_tstoi(m_sFontSize));

	RedrawPreivewText();
}


void CFont_CreationDlg::OnCbnSelchangeFontsize2()
{
	int cursel = m_wFontContrast.GetCurSel();
	m_FontContrast = (int)m_wFontContrast.GetItemData(cursel);
	RedrawPreivewText();
}

void CFont_CreationDlg::OnCbnEditchangeFontsize2()
{
	UpdateData();
	RedrawPreivewText();
}

void CFont_CreationDlg::OnCbnSelchangeFontWeight()
{
	int cursel = m_wFontWeight.GetCurSel();
	RedrawPreivewText();
}

void CFont_CreationDlg::OnCbnEditchangeFontWeight()
{
	UpdateData();
	m_FontContrast = _tstoi(m_sFontContrast);
	RedrawPreivewText();
}


void CFont_CreationDlg::OnCbnSelchangeFontAa()
{
	m_FontAntiAliasMode = m_wFontAA.GetCurSel();
	m_wFontContrast.EnableWindow(m_FontAntiAliasMode>2);
	RedrawPreivewText();
}

void CFont_CreationDlg::OnCbnSelchangeFontQuality()
{
	m_FontQuality = m_wFontQuality.GetCurSel()-1;
	RedrawPreivewText();
}

void CFont_CreationDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_bShowGrid = !m_bShowGrid;
	RedrawPreivewText();
}


void CFont_CreationDlg::OnBnClickedButtonCopy()
{
	//Copy();
}

void CFont_CreationDlg::OnBnClickedButtonPaste()
{
	//if(Paste())
	//{
	//	m_FontSelected = m_FontList.SearchFont(m_FaceName);
	//	m_CodeAreaFontIndex[m_SelectedCodeArea] = m_FontSelected;
	//}
}


void CFont_CreationDlg::OnCbnDropdownFontlist()
{
	if(!m_IsFontListUpdated)
	{
		UpdateFontList(true);

		m_IsFontListUpdated = true;

		if(m_CodeAreaFontInfo[m_SelectedCodeArea].IsAvailable())
			SelectFontList(m_CodeAreaFontInfo[m_SelectedCodeArea].m_FaceName);
		else
		{
			if(m_wFontPicker.GetCount())
			{
				m_wFontPicker.SetCurSel(0);
				m_FontSelected = (UINT)m_wFontPicker.GetItemData(0);
			}
		}
	}
}

void CFont_CreationDlg::OnBnClickedCheck1()
{
	UpdateData();
	RedrawPreivewText();
}

void CFont_CreationDlg::OnBnClickedFontBold5()
{
	UpdateData();

	if(m_FixedWidth)
	{
		m_wFixedWidth.SetWindowText(L"   Fixed Width:");
		m_WidthShrink = rt::max(m_WidthShrink,8);
	}
	else
		m_wFixedWidth.SetWindowText(L"    R-Margin:");

	RedrawPreivewText();

}

void CFont_CreationDlg::OnEnChangeEdit3()
{
	UpdateData();
	RedrawPreivewText();
}

void CFont_CreationDlg::OnEnChangeEdit4()
{
	UpdateData();
	if(m_FixedWidth)m_WidthShrink = rt::max(m_WidthShrink,8);
	RedrawPreivewText();
}

void CFont_CreationDlg::OnEnChangeEdit5()
{
	UpdateData();
	RedrawPreivewText();
}

void CFont_CreationDlg::OnEnChangeEdit2()
{
	UpdateData();
	m_FontHeight = rt::max(m_FontHeight,6U);
	RedrawPreivewText();
}



void CFont_CreationDlg::OnBnClickedButtonExport()
{
	USE_FILE_DIALOG(GetSafeHwnd(),L"Unicode Chart Font Setting (*.ucf)\0*.ucf\0");
	LPTSTR p = GET_FILENAME(false);
	if(p)
	{
		APPEND_EXTNAME(p,L".ucf");
		os::File file;
		DWORD sign = 0x46435523;

		if(file.Open(os::__UTF8(p),os::File::Normal_Write))
		{	
			file.Write(&sign,sizeof(DWORD));
			file.Write(&m_FontHeight,sizeof(m_FontHeight));
			file.Write(&m_SelectedCodeArea,sizeof(m_SelectedCodeArea));
			file.Write(m_CodeAreaFontInfo,sizeof(m_CodeAreaFontInfo));
			file.Write(m_CodeAreaChecked,sizeof(m_CodeAreaChecked));
			file.Write(&m_CodeAreaCheckedCount,sizeof(m_CodeAreaCheckedCount));
			file.Write(&m_CharacterCount,sizeof(m_CharacterCount));

			bool RegionChecked[UR_REGION_MAX];
			for(UINT i=0;i<UR_REGION_MAX;i++)
				RegionChecked[i] = m_wChartTree.GetCheck(m_RegionEntry[i]);
			file.Write(RegionChecked,sizeof(RegionChecked));

			file.Close();

			if(file.ErrorOccured())
			{
				os::File::Remove(os::__UTF8(p));
				AfxMessageBox(L"Failed to save the exporting file !!");
			}
		}
	}
}

void CFont_CreationDlg::OnBnClickedButtonSave()
{
	m_CodeAreaFontInfo[m_SelectedCodeArea].CopyFontInfo(*this);
}

void CFont_CreationDlg::OnBnClickedButtonSave2()
{
	HTREEITEM hmyItem = m_wChartTree.GetParentItem(m_CodeAreaEntry[m_SelectedCodeArea]);
	HTREEITEM hChildItem = m_wChartTree.GetChildItem(hmyItem);

	while (hChildItem != NULL)
	{
		UINT areaid = (UINT)m_wChartTree.GetItemData(hChildItem);
		m_CodeAreaFontInfo[areaid].CopyFontInfo(*this);
		hChildItem = m_wChartTree.GetNextItem(hChildItem, TVGN_NEXT);
	}
}


void CFont_CreationDlg::OnBnClickedButtonImport()
{
	USE_FILE_DIALOG(GetSafeHwnd(),L"Unicode Chart Font Setting (*.ucf)\0*.ucf\0");
	LPCTSTR p = GET_FILENAME(true);
	if(p)
	{
		os::File file;
		DWORD sign;

		if(file.Open(os::__UTF8(p),os::File::Normal_Read))
		{	
			file.Read(&sign,sizeof(DWORD));
			if(sign==0x46435523)
			{
				file.Read(&m_FontHeight,sizeof(m_FontHeight));
				file.Read(&m_SelectedCodeArea,sizeof(m_SelectedCodeArea));
				file.Read(m_CodeAreaFontInfo,sizeof(m_CodeAreaFontInfo));
				file.Read(m_CodeAreaChecked,sizeof(m_CodeAreaChecked));
				file.Read(&m_CodeAreaCheckedCount,sizeof(m_CodeAreaCheckedCount));
				file.Read(&m_CharacterCount,sizeof(m_CharacterCount));

				bool RegionChecked[UR_REGION_MAX];
				file.Read(RegionChecked,sizeof(RegionChecked));

				file.Close();

				for(UINT i=0;i<UR_REGION_MAX;i++)
					m_wChartTree.SetCheck(m_RegionEntry[i],RegionChecked[i]);

				for(UINT i=0;i<UNICODE_CHART_SIZE;i++)
					m_wChartTree.SetCheck(m_CodeAreaEntry[i],false);
				for(UINT i=0;i<m_CodeAreaCheckedCount;i++)
					m_wChartTree.SetCheck(m_CodeAreaEntry[m_CodeAreaChecked[i]],true);

				UpdateData(false);

				m_IsFontListUpdated = false;
				m_wChartTree.SelectItem(m_CodeAreaEntry[m_SelectedCodeArea]);
			}
			else
				AfxMessageBox(L"File is in bad format.");
		}
	}
}

void CFont_CreationDlg::OnCbnSelchangeCombo1()
{
	UpdateData();
	RedrawPreivewText();
}

void CFont_CreationDlg::OnBnClickedDisplayInvert()
{
	UpdateData();
	RedrawPreivewText();
}

void SwizzleTexture(LPBYTE pDst, LPCBYTE pSrc, UINT byte_per_scanline, UINT height)
{
	ASSERT(byte_per_scanline%16==0);
	ASSERT(height%8==0);

	ASSERT(pSrc!=pDst);		// MUST not be inplace
	ASSERT((((DWORD)pDst)&0x3)==0);  // aligned pointer
	ASSERT((((DWORD)pSrc)&0x3)==0);

	UINT blockx, blocky;
	UINT j;

	UINT width_blocks = (byte_per_scanline / 16);
	UINT height_blocks = (height / 8);

	UINT src_pitch = (byte_per_scanline-16)/4;
	UINT src_row = byte_per_scanline * 8;

	const BYTE* ysrc = pSrc;
	DWORD* dst = (DWORD*)(BYTE*)pDst;

	for (blocky = 0; blocky < height_blocks; ++blocky)
	{
		const BYTE* xsrc = ysrc;
		for (blockx = 0; blockx < width_blocks; ++blockx)
		{
			const DWORD* src = (DWORD*)xsrc;
			for (j = 0; j < 8; ++j)
			{
				*(dst++) = *(src++);
				*(dst++) = *(src++);
				*(dst++) = *(src++);
				*(dst++) = *(src++);
				src += src_pitch;
			}
			xsrc += 16;
		}
		ysrc += src_row;
	}
}

#include <vector>
#include <map>

void CFont_CreationDlg::OnBnClickedButtonGenerate()
{
	UpdateData();

	if(m_bSwizzleMap && (m_FontHeight&0x7))
	{
		MessageBox(L"The font height of Swizzled Glyph must be multiple of 8.");
		return;
	}

	int BPP = 1<<m_PixelFormat;
	m_GlyphLineWidth = 512 << m_GlyphLineWidthIndex;

	//if(m_FontHeight&3 || (BPP==1 && (m_FontHeight&7)) )
	//{
	//	MessageBox(L"Glyph height must be multiple of 4 for 8/4/2BPP pixel format and multiple of 8 for 1BPP pixel format.");
	//	return;
	//}

	/////////////////////////////////////////////////
	// 1. Check font group
	std::vector<std::pair<_FontGroup,UINT> > font_group;

	UINT GlyphIndex_Len = 0;
	for(UINT checked=0;checked<m_CodeAreaCheckedCount;checked++)
	{
		UINT i=m_CodeAreaChecked[checked];
		if(m_CodeAreaFontInfo[i].IsAvailable()) // selected
		{
			_FontGroup fg;
			fg.CodeMin = unicode::g_UnicodeCharts[i].CodeStart;
			fg.CodeMax = unicode::g_UnicodeCharts[i].CodeEnd;
			fg.Margin = m_CodeAreaFontInfo[i].m_LeftMargin;
			fg.Baseline = m_CodeAreaFontInfo[i].m_Baseline;

			if(m_CodeAreaFontInfo[i].m_FixedWidth)
			{
				fg.GlyphWidth_IndexOffset = (int)m_CodeAreaFontInfo[i].m_WidthShrink;
				fg.GlyphWidth_IndexOffset = -fg.GlyphWidth_IndexOffset;
			}
			else
			{	
				fg.GlyphWidth_IndexOffset = GlyphIndex_Len;
				GlyphIndex_Len += fg.CodeMax - fg.CodeMin + 1;
			}

			font_group.push_back(std::pair<_FontGroup,UINT>(fg,i));
		}
	}


	if(font_group.size()==0)
	{
		MessageBox(L"No font group is selected and saved.");
		return;
	}


	USE_FILE_DIALOG(*this,_T("Unicode Font Glyph Bitmap (*.ufg)\0*.ufg\0"));
	LPTSTR pFn = GET_FILENAME(false);
	if(!pFn)return;
	APPEND_EXTNAME(pFn,_T(".ufg"));

	m_gdiFont.Close();

	os::File	file;
	if(file.Open(os::__UTF8(pFn),os::File::Normal_Write))
	{
		ASSERT(!file.ErrorOccured());

		/////////////////////////////////////////////////
		// 2. Preparing File Header and Index Tables
		_FontGlyphIndex* pGlyphIndexTable = NULL;
		if(GlyphIndex_Len)
		{
			pGlyphIndexTable = new _FontGlyphIndex[GlyphIndex_Len];
			memset(pGlyphIndexTable,0xff,sizeof(_FontGlyphIndex)*GlyphIndex_Len);
		}

		_UFG_Header header;
		header.Sign = _UFG_Header::SIGN_MAGIC;
		header.Flag_BPP = BPP | (m_bSwizzleMap?_UFG_Header::Flag_Swizzled_GlyphLine:0);
		header.GlyphHeight = m_FontHeight;
		header.GlyphStep = m_GlyphLineWidth;
		header.FontGroupCount = (UINT)font_group.size();
		header.FontGroups_Offset = sizeof(header);
		header.GlyphIndexTable_Offset = header.FontGroups_Offset + sizeof(_FontGroup)*font_group.size();
		header.GlyphIndexTable_Size = GlyphIndex_Len*sizeof(_FontGlyphIndex);
		header.GlyphBitmap_Offset = header.GlyphIndexTable_Offset + header.GlyphIndexTable_Size;
		header.GlyphBitmap_Size = 0;

		file.Seek(sizeof(_UFG_Header));
		ASSERT(!file.ErrorOccured());

		//////////////////////////////////////////////////
		// 2. grab font glyph for all font groups
		rt::BufferEx<LPBYTE>	GlyphBitmap;  // all glyph maps after value mapping

		{	ATL::CImage glyph_line;
			UINT		GlyphLine_x = 0;

			glyph_line.Create(m_GlyphLineWidth,-((int)m_FontHeight),24);
			HDC img_dc = glyph_line.GetDC();
			Graphics	line_g(img_dc);
			SolidBrush	tx(Color(255,255,255));
			SolidBrush	bg(Color(0,0,0));
			RectF layoutRect(0, 0, 0, 0);

			for(UINT i=0;i<font_group.size();i++)
			{
				//////////////////////////////////////////////////
				// 2.1 Save font group header
				_FontGroup& fg = font_group[i].first;
				FontInfo& fi = m_CodeAreaFontInfo[font_group[i].second];

				_LOG("\t"<<(fg.CodeMax-fg.CodeMin+1)<<"\t ["<<unicode::g_RegionNames[unicode::g_UnicodeCharts[font_group[i].second].Region]<<"/");
				_LOG(unicode::g_UnicodeCharts[font_group[i].second].Name<<"]\n");

				//////////////////////////////////////////////////
				// 2.2 Create Font and value mapping
				CFont gdi_font;
				gdi_font.CreateFont(fi.m_FontSize,0,0,0,
									fi.m_FontBold?800:400,fi.m_FontItalic,
									fi.m_FontUnderline,fi.m_FontStrikeout,
									0x0,0x3,0x2,ANTIALIASED_QUALITY,0x22,fi.m_FaceName);

				Font f(img_dc,gdi_font);

				line_g.SetTextRenderingHint((TextRenderingHint)fi.m_FontAntiAliasMode);
				line_g.SetCompositingQuality((CompositingQuality)fi.m_FontQuality);
				line_g.SetTextContrast(100);

				BYTE value_mapping[256];

				if(fi.m_FontAntiAliasMode>2)
				{
					for(int i=0;i<256;i++)value_mapping[i] = (BYTE)(255.0*pow(i/255.0,fi.m_FontContrast/100.00) + 0.5);
				}
				else
				{
					for(int i=0;i<255;i++)value_mapping[i] = i;
				}

				if(!m_bInvert)
				{
					for(int i=0;i<256;i++)value_mapping[i] = 255 - value_mapping[i];
				}

				//////////////////////////////////////////////////
				// 2.3 Align starting point
				int width = -fg.GlyphWidth_IndexOffset;
				if(fi.m_FixedWidth)
				{	//align starting location of Fixed-Width glyph
					if(m_GlyphLineWidth%width==0)
					{	// align to multiple of glyph width
						GlyphLine_x = (GlyphLine_x+width-1)/width;
						GlyphLine_x *= width;
					}
					else
					{	// new line
						UINT len = m_FontHeight*m_GlyphLineWidth;
						LPBYTE p = _Malloc32AL(BYTE,len);
						memset(p, 0, len);
						LPBYTE s = (LPBYTE)glyph_line.GetBits();
						ASSERT(len*3 == glyph_line.GetPitch()*m_FontHeight);

						for(UINT i=0;i<len;i++)
							p[i] = (s[3*i] + s[3*i+1] + s[3*i+2])/3;
						GlyphBitmap.push_back(p);

						//memset(s,value_mapping[255],len*3);
						memset(s,0,len*3);
						GlyphLine_x = 0;
					}
				}

				fg.GlyphBitmap_PixelStart = GlyphBitmap.GetSize()*m_GlyphLineWidth + GlyphLine_x;
				// Write font group header
				file.Write(&fg,sizeof(_FontGroup));


				//////////////////////////////////////////////////
				// 2.4 Print all charactors
				_FontGlyphIndex* pGlyphIndex = &pGlyphIndexTable[fg.GlyphWidth_IndexOffset];

				UINT offset = 0;
				for(WCHAR c=fg.CodeMin; c<=fg.CodeMax;	c++, offset++)
				{
					if(!fi.m_FixedWidth)
					{	//determine width
						RectF boundRect;
						if(c!=L' ')
							line_g.MeasureString(&c,1,&f,layoutRect,&boundRect);
						else
						{	WCHAR h = L't';
							line_g.MeasureString(&h,1,&f,layoutRect,&boundRect);
						}

						width = (int)boundRect.Width-(fi.m_LeftMargin+fi.m_WidthShrink);
					}

					if(width>0)
					{
						if((int)GlyphLine_x+width>m_GlyphLineWidth) // new Glyph Line
						{
							UINT len = m_FontHeight*m_GlyphLineWidth;
							LPBYTE p = _Malloc32AL(BYTE,len);
							LPBYTE s = (LPBYTE)glyph_line.GetBits();
							ASSERT(len*3 == glyph_line.GetPitch()*m_FontHeight);
							_CheckHeap;

							for(UINT i=0;i<len;i++)
								p[i] = (s[3*i] + s[3*i+1] + s[3*i+2])/3;
							GlyphBitmap.push_back(p);
							_CheckHeap;

							memset(s,value_mapping[255],len*3);
							GlyphLine_x = 0;
							_CheckHeap;
						}

						if(!fi.m_FixedWidth)
						{
							UINT px_off = GlyphBitmap.GetSize()*m_GlyphLineWidth + GlyphLine_x;
							ASSERT(px_off<0xffffff);
							pGlyphIndex[offset].SetValue(rt::max(0,width),px_off);
						}

						line_g.FillRectangle(&bg,GlyphLine_x,0,width,m_FontHeight);
						line_g.DrawString(&c,1,&f,PointF((float)(((int)GlyphLine_x)-fi.m_LeftMargin),(float)-fi.m_Baseline),&tx);

						// Apply value mapping
						for(UINT y=0;y<m_FontHeight;y++)
						{
							LPBYTE p = (LPBYTE)glyph_line.GetPixelAddress(GlyphLine_x,0);
							for(UINT k=0;k<width*3U;k++)
								p[k] = value_mapping[p[k]];
						}

						GlyphLine_x += width;
					}
					else
					{
						if(!fi.m_FixedWidth)
						{
							UINT px_off = GlyphBitmap.GetSize()*m_GlyphLineWidth + GlyphLine_x;
							pGlyphIndex[offset].SetValue(0,px_off);
						}
					}
				}
			}

			//////////////////////////////////////////////////
			// 2.5 add last line
			if(GlyphLine_x)
			{
				UINT len = m_FontHeight*m_GlyphLineWidth;
				LPBYTE p = _Malloc32AL(BYTE,len);
				LPBYTE s = (LPBYTE)glyph_line.GetBits();
				ASSERT(len*3 == glyph_line.GetPitch()*m_FontHeight);

				for(UINT i=0;i<len;i++)
					p[i] = (s[3*i] + s[3*i+1] + s[3*i+2])/3;
				GlyphBitmap.push_back(p);
			}

			glyph_line.ReleaseDC();
		}

		//////////////////////////////////////////////////
		// 3. grab font glyph for all font groups
		file.Seek(header.GlyphIndexTable_Offset);
		file.Write(pGlyphIndexTable,sizeof(_FontGlyphIndex)*GlyphIndex_Len);

		ASSERT(!file.ErrorOccured());


		{	ATL::CImage	 dump;
			dump.Create(m_GlyphLineWidth,-(int)m_FontHeight*GlyphBitmap.GetSize(),8);

			RGBQUAD ct[256];
			for(UINT i=0;i<256;i++)
			{
				ct[i].rgbBlue = i;
				ct[i].rgbGreen = i;
				ct[i].rgbRed = i;
				ct[i].rgbReserved = 0;
			}
			dump.SetColorTable(0,256,ct);
			memset(dump.GetBits(), 0, m_GlyphLineWidth*m_FontHeight*GlyphBitmap.GetSize());

			for(UINT i=0;i<GlyphBitmap.GetSize();i++)
			{
				memcpy(	((LPBYTE)dump.GetBits()) + m_FontHeight*m_GlyphLineWidth*i,
						GlyphBitmap[i],m_FontHeight*m_GlyphLineWidth);
			}

			dump.Save(L"GlyphImage.png");
		}

		_LOG("Converting pixel format ...");
		/////////////////////////////////////////////////////
		// 4. convert glyph bitmap to specific pixel format and Save
		{	UINT line_size;
			if(BPP == 4)
			{	line_size = m_FontHeight*m_GlyphLineWidth/2;
				for(UINT i=0;i<GlyphBitmap.GetSize();i++)
				{
					LPBYTE s = GlyphBitmap[i];
					LPBYTE d = GlyphBitmap[i];

					for(UINT p=0;p<line_size;p++)
					{
						d[p] =	 (s[2*p+1] & 0xf0)	 |
								((s[2*p+0]       )>>4);
					}
				}
			}
			else if(BPP == 2)
			{	line_size = m_FontHeight*m_GlyphLineWidth/4;
				for(UINT i=0;i<GlyphBitmap.GetSize();i++)
				{
					LPBYTE s = GlyphBitmap[i];
					LPBYTE d = GlyphBitmap[i];

					for(UINT p=0;p<line_size;p++)
					{
						d[p] =	 (s[4*p+3] & 0xc0)	  |
								((s[4*p+2] & 0xc0)>>2)|
								((s[4*p+1] & 0xc0)>>4)|
								((s[4*p+0]       )>>6);
					}
				}
			}
			else if(BPP == 1)
			{	line_size = m_FontHeight*m_GlyphLineWidth/8;
				for(UINT i=0;i<GlyphBitmap.GetSize();i++)
				{
					LPBYTE s = GlyphBitmap[i];
					LPBYTE d = GlyphBitmap[i];

					for(UINT p=0;p<line_size;p++)
					{
						d[p] =	 (s[8*p+7] & 0x80)	  |
								((s[8*p+6] & 0x80)>>1)|
								((s[8*p+5] & 0x80)>>2)|
								((s[8*p+4] & 0x80)>>3)|
								((s[8*p+3] & 0x80)>>4)|
								((s[8*p+2] & 0x80)>>5)|
								((s[8*p+1] & 0x80)>>6)|
								((s[8*p+0]       )>>7);
					}
				}
			}
			else
			{	line_size = m_FontHeight*m_GlyphLineWidth;
			}

			header.GlyphBitmap_Size = line_size*GlyphBitmap.GetSize();
			file.Seek(header.GlyphBitmap_Offset);
			rt::BufferEx<BYTE>	buf;
			buf.SetSize(line_size);
			for(UINT i=0;i<GlyphBitmap.GetSize();i++)
			{
				if(m_bSwizzleMap)
				{
					SwizzleTexture(buf,GlyphBitmap[i],line_size/m_FontHeight,m_FontHeight);
					file.Write(buf,line_size);
				}
				else
				{
					file.Write(GlyphBitmap[i],line_size);
				}
				_SafeFree32AL(GlyphBitmap[i]);
			}
		}

		ASSERT(!file.ErrorOccured());

		/////////////////////////////////////////////////////
		// 5. Save header
		file.Seek(0);
		file.Write(&header,sizeof(header));

		ASSERT(!file.ErrorOccured());

		if(file.ErrorOccured())
		{	
			_LOG("\nFont Generation failed");
		}
		else
			_LOG("\nUnicode Font Glyph Lib has been saved to:\n\t"<<pFn<<"\n");

		_SafeDelArray(pGlyphIndexTable);
	}
	else
	{
		_LOG("Failed to open "<<pFn<<"\n");
	}

}


void CFont_CreationDlg::OnBnClickedButtonTestUfg()
{
	USE_FILE_DIALOG(*this, _T("Unicode Font Glyph (*.ufg)\0*.ufg\0"));
	LPCTSTR p = GET_FILENAME(true);

	_CheckHeap;

	if(p)
	{
		if(m_gdiFont.Open(os::__UTF8(p),gl::gdiFont::FLAG_KEEP_IN_MEMORY))
		{
			UINT W = m_FontImage.GetWidth();
			UINT H = m_FontImage.GetHeight();
			UINT CH = m_gdiFont.GetGlyphMaxHeight();
			HDC  dc = m_FontImage.GetDC();

			//m_gdiFont.SetTextColor(RGB(200,10,10),RGB(100,220,222));

			memset(m_FontImage.GetBits(),0,H*m_FontImage.GetPitch());
			_CheckHeap;

			//LPCWSTR text = L"Hello#!! 你好啊  なれおん عفوا لا توجد  Lcióepí rtážemě  廣播節目網站  λαμβάνετε  פשוט מדפיסה  현대오일뱅  Программа  ศไทยและประเทศ";
			LPCWSTR text = L"⅛  ∆Hello World∆    ∆喂，世界∆   ∆首一個∆   ∆あいさつ世界∆   ∆여보，전세계의∆     ∆Привет мир∆   ∆Lcióepí rtážemě∆    ∆הלו!,חיי העולם הזה∆   ∆هتاف للترحيب الشؤون∆    ∆χαιρετισμόσ,κόσμοσ∆     ∆สวัสดี  ชาวโลก∆      ∫∑∞⌂⅛⅜⅝⅞    ↔→↑←↓";
			UINT len = (UINT)wcslen(text);

			ATL::CImage glyph;
			if(glyph.Create(m_gdiFont.GetPixelStep(), -((int)m_gdiFont.GetGlyphMaxHeight()),m_gdiFont.GetBPP()))
			{
				UINT col = 1<<m_gdiFont.GetBPP();
				RGBQUAD ct[256];
				for(UINT i=0;i<col;i++)
				{
					ct[i].rgbBlue  = i*255/(col-1);
					ct[i].rgbGreen = i*255/(col-1);
					ct[i].rgbRed   = i*255/(col-1);
					ct[i].rgbReserved = 0;
				}

				glyph.SetColorTable(0,col,ct);
				LPBYTE pG = (LPBYTE)glyph.GetBits();
				UINT g_step = glyph.GetPitch();
				UINT font_step = m_gdiFont.GetStep();

				UINT x = 0, y = 0;
				for(UINT i=0;i<len && y<H-CH;i++)
				{
					int sx,sw,sh;
					LPCBYTE p = m_gdiFont.GetGlyph(text[i],sx,sw,sh);

					ASSERT(sx+sw<=512);

					_CheckHeap;
					if(p)
					{
						for(int sy=0;sy<sh;sy++)
							memcpy(pG+g_step*sy,p+font_step*sy,(sx+sw)*m_gdiFont.GetBPP()/8);

						if(m_gdiFont.GetBPP()==4)
						{
							for(UINT i=0;i<(UINT)glyph.GetHeight()*glyph.GetPitch();i++)
								pG[i] = (pG[i]>>4) | (pG[i]<<4);
						}

						if(x+sw >= W)
						{
							x=0;
							y+=CH;
						}

						glyph.Save(L"g.png");

						glyph.Draw(dc,x,y,sw,sh,sx,0,sw,sh);
						_CheckHeap;

						x+=sw;

					}
				}
				RedrawPreviewImage();
			}
			
			_CheckHeap;

			m_FontImage.ReleaseDC();
		}
	}
	_CheckHeap;
}

void CFont_CreationDlg::OnEnChangeTestText()
{
	UpdateData();

	if(m_gdiFont.IsOpen())
	{
		UINT W = m_FontImage.GetWidth();
		UINT H = m_FontImage.GetHeight();
		UINT CH = m_gdiFont.GetGlyphMaxHeight();
		HDC  dc = m_FontImage.GetDC();

		//m_gdiFont.SetTextColor(RGB(200,10,10),RGB(100,220,222));

		memset(m_FontImage.GetBits(),0,H*m_FontImage.GetPitch());
		_CheckHeap;

		LPCWSTR text = m_sTestText;
		UINT len = (UINT)wcslen(text);

		ATL::CImage glyph;
		if(glyph.Create(m_gdiFont.GetGlyphMaxWidth(), -((int)m_gdiFont.GetGlyphMaxHeight()),m_gdiFont.GetBPP()))
		{
			UINT col = 1<<m_gdiFont.GetBPP();
			RGBQUAD ct[256];
			for(UINT i=0;i<col;i++)
			{
				ct[i].rgbBlue = i*255/(col-1);
				ct[i].rgbGreen = i*255/(col-1);
				ct[i].rgbRed = i*255/(col-1);
				ct[i].rgbReserved = 0;
			}

			glyph.SetColorTable(0,col,ct);
			LPBYTE pG = (LPBYTE)glyph.GetBits();
			UINT g_step = glyph.GetPitch();
			UINT font_step = m_gdiFont.GetStep();

			UINT x = 0, y = 0;
			for(UINT i=0;i<len && y<H-CH;i++)
			{
				int sx,sw,sh;
				LPCBYTE p = m_gdiFont.GetGlyph(text[i],sx,sw,sh);

				_CheckHeap;
				if(p)
				{
					for(int sy=0;sy<sh;sy++)
						memcpy(pG+g_step*sy,p+font_step*sy,sw*m_gdiFont.GetBPP()/8);

					if(x+sw >= W)
					{
						x=0;
						y+=CH;
					}

					glyph.Draw(dc,x,y,sw,sh,sx,0,sw,sh);
					_CheckHeap;

					x+=sw;

				}
			}
			RedrawPreviewImage();
		}
		
		_CheckHeap;

		m_FontImage.ReleaseDC();
	}
}

void CFont_CreationDlg::OnBnClickedButtonImg2array()
{
	USE_FILE_DIALOG(*this,_T("Image Files (*.jpg;*.png;*.bmp)\0*.jpg;*.png;*.bmp\0All Files (*.*)\0*.*\0"));
	LPTSTR p = GET_FILENAME(true);
	if(p)
	{
		ATL::CImage img;
		if(SUCCEEDED(img.Load(p)))
		{
			os::File	text;
			REPLACE_EXTNAME(p,_T(".cpp"));
			text.Open(os::__UTF8(p),os::File::Normal_Write);
			fprintf(text.GetFileHandle(),"static const DWORD pixels[] = \n{ // %dx%d",img.GetWidth(),img.GetHeight());
			int y=0;
			for(;y<img.GetHeight();y++)
			{
				fprintf(text.GetFileHandle(),"\r\n\t");
				for(int x=0;x<img.GetWidth();x++)
				{	LPBYTE p = (LPBYTE)img.GetPixelAddress(x,y);
					rt::Swap(p[0],p[2]);
					fprintf(text.GetFileHandle(),"0x%08x,",*((DWORD*)p));
				}
			}
			fprintf(text.GetFileHandle(),"\r\n\t0\r\n};\r\n");
		}
	}
}

void CFont_CreationDlg::OnBnClickedButtonCopycode()
{
	if(m_SelectedCodeArea>=0 && m_SelectedCodeArea<sizeofArray(unicode::g_UnicodeCharts))
	{
		const unicode::ChartArea& ca = unicode::g_UnicodeCharts[m_SelectedCodeArea];
		CString text;
		text.Format(_T("Unicode Region: %s/%s (0x%04x-0x%04x)\15\12"),
					ca.Name,
					unicode::g_RegionNames[ca.Region],
					ca.CodeStart,
					ca.CodeEnd);

		int co = rt::min(256U,ca.CodeEnd - ca.CodeStart);
		CString str;
		for(int i=0;i<co;i++)
		{	WORD c = i+ca.CodeStart;
			str.Format(_T("\\x%02x\\x%02x  %c\15\12"),c&0xff,c>>8,(WCHAR)c);
			text += str;
		}

		::OpenClipboard(NULL); 

		LPCWSTR string = text;
		EmptyClipboard();
		int cch = (int)_tcslen(string);

		HGLOBAL hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (cch + 1) * sizeof(TCHAR)); 
		if(hglbCopy)
		{

		LPVOID lptstrCopy = GlobalLock(hglbCopy); 
		ASSERT(lptstrCopy);
		memcpy(lptstrCopy, string,(cch+1) * sizeof(TCHAR)); 
		GlobalUnlock(hglbCopy); 

	#ifdef UNICODE
		SetClipboardData(CF_UNICODETEXT, hglbCopy);
	#else
		SetClipboardData(CF_TEXT, hglbCopy);
	#endif
		}
		
		::CloseClipboard();
	}
}
