//
//  422ToNv16.h
//  422ToNv16
//
//  Created by Hank Lee on 7/14/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//

#ifndef ___422ToNv16___
#define ___422ToNv16___


int planar_to_interleave
(
        uint32_t wxh,
        uint8_t *dst,
  const uint8_t *u,
  const uint8_t *v
 );


#endif