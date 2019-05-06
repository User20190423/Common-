//ʹӦ�ó���ֻ������һ��ʵ��
//
//Windows�Ƕ���̲���ϵͳ��������ɵ�Ӧ�ó�����Զ�����У��γɶ������ʵ����
//������Щ�����Ϊ��֤Ӧ�ó���İ�ȫ���У�Ҫ�����ֻ������һ��ʵ���������
//��Ҫʹ��ֻ�ܱ�һ�����̵���ʹ�õ�����Ӳ����������ƽ������ʱ���������Ƴ�
//��ֻ����һ��ʵ����
//
//�����漰�������������⣬һ���ڳ���ĵڶ���ʵ������ʱ����η��ָó�������
//һ��ʵ�������У�������ν���һ��ʵ��������ڶ���ʵ���˳���
//
//���ڵ�һ�����⣬����ͨ����Ӧ�ó��������ź�����ʵ������ʱ���ȼ����ź�����
//���Ѵ��ڣ���˵������������һ��ʵ����
//
//�ڶ���������ѵ��ǻ�ȡ��һ��ʵ������������ָ�������Ȼ������
//SetForegroundWindow�������ȻFindWindow������Ѱ���������ŵĴ��ڣ����ú�
//��Ҫ��ָ����Ѱ�Ҵ��ڵı���򴰿�����������ʵ��ͨ�÷�����;����
//���ǿ�����Win32 SDK����SetProp����Ӧ�ó�����������һ�����еı�ǡ�
//��GetDesktopWindow ���Ի�ȡWindowsϵͳ���ش��ڶ���ָ�����������Ӧ�ó�
//���������ɿ��ɸô��ڵ��Ӵ��ڣ�������GetWindow������������ǵĶ���ָ����
//������Win32 SDK����GetProp����ÿһӦ�ó��������Ƿ�������������õ��ض���
//�Ǳ��ȷ�����Ƿ�����ҪѰ�ҵĵ�һ��ʵ��������ʹ�ڶ���ʵ���˳��ܼ򵥣�ֻҪ
//����Ӧ�ó�������InitInstance��������FALSE���ɡ����⣬���������˳�ʱ��Ӧ
//��RemoveProp����ɾ������Ϊ�����õı�ǡ�
//
//�����InitInstance��OnCreate��OnDestroy�������뽫ʵ�������Ĳ�����

BOOL CEllipseWndApp::InitInstance()
{
	// ��Ӧ�ó����������ź��� 
	HANDLE hSem = CreateSemaphore(NULL, 1, 1, m_pszExeName);

	// �ź����Ѵ��ڣ� 
	// �ź������ڣ����������һ��ʵ������ 
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		// �ر��ź������ 
		CloseHandle(hSem);
		// Ѱ����ǰʵ���������� 
		HWND hWndPrevious = ::GetWindow(::GetDesktopWindow(), GW_CHILD);
		while (::IsWindow(hWndPrevious))
		{
			// ��鴰���Ƿ���Ԥ��ı��? 
			// �У���������Ѱ�ҵ����� 
			if (::GetProp(hWndPrevious, m_pszExeName))
			{
				// ����������С������ָ����С 
				if (::IsIconic(hWndPrevious))
					::ShowWindow(hWndPrevious, SW_RESTORE);

				// ���������� 
				::SetForegroundWindow(hWndPrevious);

				// �������ĶԻ��򼤻� 
				::SetForegroundWindow(
					::GetLastActivePopup(hWndPrevious));

				// �˳���ʵ�� 
				return FALSE;
			}
			// ����Ѱ����һ������ 
			hWndPrevious = ::GetWindow(hWndPrevious, GW_HWNDNEXT);
		}
		// ǰһʵ���Ѵ��ڣ����Ҳ��������� 
		// ���ܳ����� 
		// �˳���ʵ�� 
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization 
	// If you are not using these features and wish to reduce the size 
	// of your final executable, you should remove from the following 
	// the specific initialization routines you do not need. 
#ifdef _AFXDLL 
	Enable3dControls(); // Call this when using MFC in a shared DLL 
#else 
	Enable3dControlsStatic();// Call this when linking to MFC statically 
#endif 

	CEllipseWndDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is 
		// dismissed with OK 
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is 
		// dismissed with Cancel 
	}
	// Since the dialog has been closed, return FALSE so that we exit the 
	// application, rather than start the application's message pump. 
	return FALSE;
}

int CEllipseWndDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	// ����Ѱ�ұ�� 
	::SetProp(m_hWnd, AfxGetApp()->m_pszExeName, (HANDLE)1);
	return 0;
}

void CEllipseWndDlg::OnDestroy()
{
	CDialog::OnDestroy();
	// ɾ��Ѱ�ұ�� 
	::RemoveProp(m_hWnd, AfxGetApp()->m_pszExeName);
}


