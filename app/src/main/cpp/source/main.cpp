//!
//! $URL: $
//!
//! @(#)$Id: $
//!
//! \file	sysmemc.c
//!
//! \brief
//!

/*****************************************************************************
**                                                                          **
** This program is the confidential and proprietary product of Application  **
** Solutions Limited and Valeo Vision Systems. Any unauthorised use,        **
** reproduction or transfer of this program is strictly prohibited.         **
** Copyright 2007 Application Solutions Limited and Valeo Vision Systems.   **
** (Subject to limited distribution and restricted disclosure only.)        **
** All rights reserved.                                                     **
**                                                                          **
*****************************************************************************/
#define LOCAL_FILENAME "main.cpp"
//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------

#include "pedapp.hpp"
#include <iostream>
#include <fstream>

#include "main.hpp"
std::ifstream infile;
int initFile = 0;
uint8_t* inputImage;
cv::VideoWriter outpuvideo;
using namespace std;
//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------

/*-------------------------------------------------------------------------*/
/*! \brief  Allocates size bytes and returns a pointer to the allocated memory.
**
** \param[in]   size Number of bytes to be allocated
**
**
** \return  Pointer to the allocated memory.
*/
int main(){

    pedapp_Init();
    outpuvideo.open("ped.avi",   cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, cv::Size(1920, 1080));
    unsigned char *Buffer=         new uint8[1920*1080*3];
    unsigned char *inputImage  =   new uint8[1344*1024*2];
    for(int i=0;i<1000;i++){
        if(initFile == 0)
        {
            infile.open("newfile.yuv", ios::in|ios::binary);
            initFile = 1;
        }

        if(infile.eof())
        {
            return false;
        }

        printf("Reading the Frame\n");
        infile.read ((char *)inputImage, 1280*806*2);
        pedapp_Process(inputImage,Buffer);
        printf("After Process  the Frame\n");

        cv::Mat Output(1080, 1920, CV_8UC3,Buffer);
        // cv::imwrite("outputimage_1.jpg",Output);
        outpuvideo.write(Output);
        printf("After Process output imwrite the Frame\n");
    }

    delete Buffer;
    delete inputImage;


}


//---------------------------------------------------------------------------
// End of File
//---------------------------------------------------------------------------

