// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���A
//            �܂��͎Q�Ɖ񐔂������A�����܂�ύX����Ȃ�
//            �v���W�F�N�g��p�̃C���N���[�h �t�@�C�����L�q���܂��B
//

#if !defined(AFX_STDAFX_H__0B36D003_CA8D_42AC_9C2D_E4CB9639889E__INCLUDED_)
#define AFX_STDAFX_H__0B36D003_CA8D_42AC_9C2D_E4CB9639889E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#pragma warning(disable:4786 4503)
#endif // _MSC_VER > 1000

#include "SmartWin.h"

/*#define WIN32_LEAN_AND_MEAN	// Windows �w�b�_�[����w�ǎg�p����Ȃ��X�^�b�t�����O���܂��B
#define _WIN32_IE	0x0550

#include <atlbase.h>
#include <atlapp.h>
#if (_ATL_VER < 0x0700)
extern CAppModule _Module;
#define _AtlBaseModule _Module
#endif
#include <atlcom.h>
#include <atlres.h>
#include <atlwin.h>
#include <atlctrls.h>
#include <atlcrack.h>
#include <atlmisc.h>
#include <atlddx.h>*/

#include <d3d9.h>
#include <d3d9types.h>
#include <d3dx9.h>
#include <dxfile.h>
#include <dmusici.h>
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>

#if defined(_DEBUG) && !defined(DEBUG)
#define DEBUG	1
#endif

#if _MSC_VER < 1300
#define for if(0); else for
#else
#pragma conform(forScope, on)
#endif

#include <gctp/def.hpp>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_STDAFX_H__0B36D003_CA8D_42AC_9C2D_E4CB9639889E__INCLUDED_)