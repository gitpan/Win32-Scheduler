#ifndef _CONSTANT_H_
#define _CONSTANT_H_

enum eConstantType { NotDefined = 0, NotPresent, String, Numeric };

eConstantType Constant( LPTSTR pszConstant, LPVOID *ppBuffer );
LPTSTR GetConstantName( DWORD dwIndex );
DWORD GetTotalConstants();
void CountConstants();

typedef struct tagConstStruct
{
    LPTSTR m_Name;
    LPVOID m_pBuffer;
    eConstantType m_eType;
} ConstantStruct;

#endif //	_CONSTANT_H_