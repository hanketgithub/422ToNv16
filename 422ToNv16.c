//
//  422ToNv16.c
//  422ToNv16
//
//  Created by Hank Lee on 7/14/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//

#include <stdint.h>

#include "422ToNv16.h"


int planar_to_interleave
(
        uint32_t wxh,
        uint8_t *dst,
  const uint8_t *u,
  const uint8_t *v
)
{
    int i;
    
    for (i = 0; i < wxh / 2; i++)
    {
        uint8_t u_data = u[i];  // fetch u data
        uint8_t v_data = v[i];  // fetch v data
        
        dst[2 * i]      = u_data;   // write u data
        dst[2 * i + 1]  = v_data;   // write v data
    }

    return 0;
}
