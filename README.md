#Dell activity LED controller

This is a simple C program to control the activity LED on a Dell Chromebook (Tested on 3120, Candy)


|Argument number|Color |
|---------------|------|
|1              |Red   |
|2              |Green |
|3              |Blue  |
|4              |Yellow|
|5              |Purple|
|6              |Cyan  |
|7              |White |
|8              |Off   |


##How does it work?

I've used https://github.com/DellSWPub/DellActivityLightSDK and https://github.com/hgeg/candy-led as reference.
Since these were written in languages i don't know, i decided to write my own implementation in C.

In `change_color()` a command is constructed, with the first byte being `0x11`, second being the color, third being the CRC and fourth a random number.
Implementations shown in the two links above show the use of a `rand()` function for the fourth byte, but i've found it can be any value and needs not be changed on each command, therefore a random number is used (0x55).

The command is then written to a device, `/dev/hidraw0`, which controls the LED.

`checksum` is used to calculate the checksum mentioned above. I've found that a command will not work without the correct CRC. 
The formula used for calculating CRC is :

`( 21 * command[0] * command[0] + 19 * command[1] - 3 * command[3] ) % 255`

##Building

Since it's only one file, i was too lazy to add a makefile. You are supposed to build it with:

`cc -o *filename* main.c
