#define mpt_getInput_h

#define MPT_NR 3
#define MPT_NX 1
#define MPT_NU 1
#define MPT_NY 1
#define MPT_NXT 1
#define MPT_NREF 0
#define MPT_TS 0.080000
#define MPT_DUMODE 0
#define MPT_TRACKING 0
#define MPT_ABSTOL 1.000000e-08

static float MPT_H[] = {
1.000000e+00,	-1.000000e+00,	-1.000000e+00,	1.000000e+00,	1.000000e+00,	
-1.000000e+00 };

static float MPT_K[] = {
1.908350e+00,	1.908350e+00,	-1.908350e+00,	3.141593e+00,	-1.908350e+00,	
3.141593e+00 };

static int MPT_NC[] = {
2,	2,	2 };

static float MPT_F[] = {
-1.646235e+00,	0.000000e+00,	0.000000e+00 };

static float MPT_G[] = {
-2.220446e-15,	-3.141593e+00,	3.141593e+00 };
