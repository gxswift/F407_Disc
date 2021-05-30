cls
@echo off
echo DTR Low reset RTS High Bootloader
echo -----------------------------------------------
STMFlashLoader.exe -c --pn 5 --br 115200 --db 8 --pr EVEN --sb 1 --ec OFF  --to 10000 --co ON -Dtr --Lo -Rts --Hi -Dtr --Hi -i STM32F4_05_07_15_17_1024K -e --all -d --fn D:\practise\F407_Disc\build\F407.hex  -Dtr --Lo -Rts --Lo -Dtr --Hi
PAUSE 