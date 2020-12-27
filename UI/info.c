/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.22                          *
*        Compiled Jul  4 2013, 15:16:01                              *
*        (c) 2013 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"
#include "stdio.h"
#include "stdint.h"
#include "stm32f4xx_hal.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0 (GUI_ID_USER + 0x00)
#define ID_BUTTON_0 (GUI_ID_USER + 0x01)
#define ID_BUTTON_1 (GUI_ID_USER + 0x02)
// USER START (Optionally insert additional defines)

// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
    {WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 40, 480, 280, 0, 0x0, 0},
    // USER START (Optionally insert additional widgets)
    {BUTTON_CreateIndirect, "Return", ID_BUTTON_0, 300, 210, 80, 40, 0, 0x0, 0},
    {BUTTON_CreateIndirect, "Upgrade", ID_BUTTON_1, 100, 210, 80, 40, 0, 0x0, 0},
    // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
extern WM_HWIN H_Hand;
#define VH 0
#define VL 0
char str[40];
// USER END

/*********************************************************************
*
*       _cbDialog
*/
extern WM_HWIN CalenderWindow(void);
extern void Startup(WM_HWIN hWin, uint16_t xpos, uint16_t ypos);
static void _cbDialog(WM_MESSAGE *pMsg)
{

  WM_HWIN hItem;
  // USER START (Optionally insert additional variables)
  int NCode;
  int Id;
  int ver_h, ver_l;
  uint32_t *CPU_ID;
  // USER END

  switch (pMsg->MsgId)
  {
  case WM_PAINT:
    GUI_DrawGradientV(0, 0, 479, 280, GUI_LIGHTBLUE, GUI_BLUE);
    GUI_SetTextMode(GUI_TM_TRANS);
    GUI_SetFont(GUI_FONT_20_1);
    ver_h = VH;
    ver_l = VL;
    sprintf(str, "version:\r\n%d.%d", ver_h, ver_l);
    GUI_DispStringHCenterAt(str, 240, 20);

    CPU_ID = (uint32_t *)(0x1fff7a10);
    sprintf(str, "CPU ID:\r\n%08X.%08X.%08X", CPU_ID[0], CPU_ID[1], CPU_ID[2]);
    GUI_DispStringHCenterAt(str, 240, 70);

    sprintf(str, "Compile time:\r\n%s--%s", __DATE__, __TIME__);
    GUI_DispStringHCenterAt(str, 240, 120);

    sprintf(str, "emwin test!");
    GUI_DispStringHCenterAt(str, 240, 170);

    break;
  case WM_INIT_DIALOG:
    //
    // Initialization of 'SoftWare'
    //

    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetFont(hItem, &GUI_Font20_1);
    BUTTON_SetText(hItem, "Return");

    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetFont(hItem, &GUI_Font20_1);
    BUTTON_SetText(hItem, "Upgrade");

    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
    // USER START (Optionally insert additional message handling)
  case WM_NOTIFY_PARENT:
    Id = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch (Id)
    {
    case ID_BUTTON_0: // Notifications sent by 'Button'
      switch (NCode)
      {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        hItem = pMsg->hWin;
        WM_DeleteWindow(hItem);
        CalenderWindow();
        //	H_Hand = SelectWindow();
        // USER END
        break;
        // USER START (Optionally insert additional code for further notification handling)
        // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'upgrade'
      switch (NCode)
      {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        /*
		  			HAL_FLASH_Unlock();
			FLASH_WaitForLastOperation((uint32_t)5000);
			if (HAL_OK!=HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,0x080E0000,0XB9F9D0C2))
				printf("write error\r\n");
			FLASH_WaitForLastOperation((uint32_t)5000);
			HAL_FLASH_Lock();
			*/
     hItem = pMsg->hWin;
    Startup(hItem,20,0);
       // NVIC_SystemReset();
        // USER END
        break;
        // USER START (Optionally insert additional code for further notification handling)
        // USER END
      }
      break;
    }
    break;
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateSoftWare
*/
WM_HWIN CreateSoftWare(void);
WM_HWIN CreateSoftWare(void)
{
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
