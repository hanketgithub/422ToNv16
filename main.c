//
//  main.c
//  422ToNv16
//
//  Created by Hank Lee on 7/14/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "422ToNv16.h"

int main(int argc, const char * argv[]) {
    int ifd;
    int ofd;
    
    uint8_t *y;
    uint8_t *u;
    uint8_t *v;
    ssize_t rd_sz;
    
    uint32_t width;
    uint32_t height;
    uint32_t wxh;
    
    uint8_t *img;
    uint8_t *u_et_v_dst;
    
    char *cp;
    char output[256] = { 0 };

    
    if (argc < 4)
    {
        fprintf(stderr, "useage: %s [input_file] [width] [height]\n", argv[0]);
        
        return -1;
    }
    
    
    rd_sz       = 0;
    width       = 0;
    height      = 0;
    wxh         = 0;
    img         = NULL;
    u_et_v_dst  = NULL;
    cp          = NULL;
    
    // get input file name from comand line
    ifd = open(argv[1], O_RDONLY);
    if (ifd < 0)
    {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }
    
    // specify output file name
    cp = strrchr(argv[1], '.');
    strncpy(output, argv[1], cp - argv[1]);
    strcat(output, "_nv16");
    strcat(output, cp);
    
    ofd = open(output, O_WRONLY | O_CREAT, S_IRUSR);
    
    width   = atoi(argv[2]);
    height  = atoi(argv[3]);
    
    wxh = width * height;
    
    img = malloc(wxh * 2);
    u_et_v_dst = malloc(wxh);
    
    y = img;
    u = y + wxh;
    v = u + wxh / 2;
    
    fprintf(stderr, "Processing: ");
    
    while (1)
    {
        rd_sz = read(ifd, img, wxh * 2);
        
        if (rd_sz == wxh * 2)
        {
            planar_to_interleave
            (
                wxh,
                u_et_v_dst,
                u,
                v
            );
            
            write(ofd, y, wxh);
            write(ofd, u_et_v_dst, wxh);
        }
        else
        {
            break;
        }
        fputc('.', stdout);
        fflush(stdout);
    }
    
    close(ifd);
    close(ofd);
    
    fprintf(stderr, "Done\n");
    fprintf(stderr, "Output file: %s\n", output);
    
    return 0;
}
