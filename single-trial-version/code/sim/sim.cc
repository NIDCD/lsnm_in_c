/*============================================================================
 *
 *                    PUBLIC DOMAIN NOTICE
 *
 *   National Institute on Deafness and Other Communication Disorders
 *
 * This software/database is a "United States Government Work" under the 
 * terms of the United States Copyright Act. It was written as part of 
 * the author's official duties as a United States Government employee and 
 * thus cannot be copyrighted. This software/database is freely available 
 * to the public for use. The NIDCD and the U.S. Government have not placed 
 * any restriction on its use or reproduction. 
 *
 * Although all reasonable efforts have been taken to ensure the accuracy 
 * and reliability of the software and data, the NIDCD and the U.S. Government 
 * do not and cannot warrant the performance or results that may be obtained 
 * by using this software or data. The NIDCD and the U.S. Government disclaim 
 * all warranties, express or implied, including warranties of performance, 
 * merchantability or fitness for any particular purpose.
 *
 * Please cite the author in any work or product based on this material.
 * 
 * ==========================================================================
 *
 */

/* **************************************************************************

   Large-Scale Neural Modeling software (LSNM)

   Section on Brain Imaging and Modeling
   Voice, Speech and Language Branch
   National Institute on Deafness and Other Communication Disorders
   National Institutes of Health

   This file (unixmain.cc) was last modified on January 18, 2015.


   Author: Malle Tagamets. Last updated by Antonio Ulloa on January 18 2015  
* **************************************************************************/

// Sim.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Sim.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "SimDoc.h"
#include "SimView.h"

void Umain(int argc, CString argv);

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimApp

BEGIN_MESSAGE_MAP(CSimApp, CWinApp)
	//{{AFX_MSG_MAP(CSimApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimApp construction

CSimApp::CSimApp()
{
	// TODO: add construction code here,

	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSimApp object

CSimApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSimApp initialization

BOOL CSimApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_SIMTYPE,
		RUNTIME_CLASS(CSimDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSimView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	
	// Dispatch commands specified on the command line
	/* TMP  We want to execute our own command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
		ETMP */

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

    Umain(2, cmdInfo.m_strFileName);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CSimApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSimApp commands