
#ifndef __CAN_H
#define __CAN_H

#include "common.h"

typedef void (*can_irq_handler)(uint32_t id);

typedef enum
{
    BSP_CAN_33KBPS = 0,              // ������ 33K ģʽ
    BSP_CAN_50KBPS,                  // ������ 50K ģʽ
    BSP_CAN_625KBPS,                 // ������ 62.5K ģʽ
    BSP_CAN_96KBPS,                  // ������ 96K ģʽ
    BSP_CAN_100KBPS,                 // ������ 100K ģʽ
    BSP_CAN_125KBPS,                 // ������ 125K ģʽ
    BSP_CAN_250KBPS,                 // ������ 250K ģʽ
    BSP_CAN_500KBPS,                 // ������ 500K ģʽ
    BSP_CAN_800KBPS,                 // ������ 800K ģʽ
    BSP_CAN_1MBPS,                   // ������ 1Mģʽ
}BSP_CAN_BAUD;

class Can
{
    public:
      	Can(Gpio* p_pin_rx, Gpio* p_pin_tx);
        void    begin(BSP_CAN_BAUD bps);
        void    set_filter(u8 Fifo,u8 nCanType,u8 num,u32 ID,u32 Mask);
        void    interrupt(FunctionalState enable);
        void    attach_interrupt(void (*callback_fun)(void));
        void    set_filter_idlist(u8 nCanType,u32 ID);
        void    set_filter_idmask(u8 nCanType,u8 num,u32 ID,u32 mask);
        void    set_filter_idlist(u8 nCanType,u8 num,u32 ID);
        u8      write(CanTxMsg *pCanMsg);
        void    read(CanRxMsg *pCanMsg);
        u8      available(void);
        void    attach(void (*fptr)(void));
    private:
        void set_bps(BSP_CAN_BAUD);
        CAN_TypeDef*    _CANx;
        Gpio*           pin_rx;           //arduino pin number
        Gpio*           pin_tx;           //arduino pin number    
        BSP_CAN_BAUD    _bps;  

};

#endif
