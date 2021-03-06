/* Include files */

#include <stddef.h>
#include "blas.h"
#include "Hquad_control_LIB_MPC_sfun.h"
#include "c8_Hquad_control_LIB_MPC.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "Hquad_control_LIB_MPC_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c8_debug_family_names[31] = { "m", "delay_steps", "N",
  "x_predicted", "U_ref", "LL_PP_ref", "MM_ref", "V_star", "U_star", "nargin",
  "nargout", "TT_PP", "LL_PP", "LL_ref_PP", "LL_U_ref_PP", "MM", "PP",
  "AA_delay", "BB_delay", "x", "X_ref", "V_max", "i_min", "betas", "L", "u_buff",
  "V_init", "u_opt", "J_star", "u_buff_out", "V_init_out" };

static const char * c8_b_debug_family_names[23] = { "MONITOR", "L_inv",
  "LL_PP_t", "V_i", "W_i", "i", "V_ip1", "W_ip1", "sol", "nargin", "nargout",
  "TT_PP", "LL_PP", "MM", "V_min", "V_max", "V_init", "i_min", "betas", "L", "J",
  "V", "actual_num_iters" };

/* Function Declarations */
static void initialize_c8_Hquad_control_LIB_MPC
  (SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance);
static void initialize_params_c8_Hquad_control_LIB_MPC
  (SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance);
static void enable_c8_Hquad_control_LIB_MPC
  (SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance);
static void disable_c8_Hquad_control_LIB_MPC
  (SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance);
static void c8_update_debugger_state_c8_Hquad_control_LIB_MPC
  (SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c8_Hquad_control_LIB_MPC
  (SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance);
static void set_sim_state_c8_Hquad_control_LIB_MPC
  (SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance, const mxArray *c8_st);
static void finalize_c8_Hquad_control_LIB_MPC
  (SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance);
static void sf_c8_Hquad_control_LIB_MPC(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance);
static void c8_chartstep_c8_Hquad_control_LIB_MPC
  (SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance);
static void initSimStructsc8_Hquad_control_LIB_MPC
  (SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance);
static void registerMessagesc8_Hquad_control_LIB_MPC
  (SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance);
static void c8_runFastGradient(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, real_T c8_TT_PP[900], real_T c8_LL_PP[30], real_T c8_MM,
  real_T c8_V_min[30], real_T c8_V_max[30], real_T c8_V_init[30], real_T
  c8_i_min, real_T c8_betas[8], real_T c8_L, real_T *c8_J, real_T c8_V[30],
  real_T *c8_actual_num_iters);
static void init_script_number_translation(uint32_T c8_machineNumber, uint32_T
  c8_chartNumber);
static const mxArray *c8_sf_marshallOut(void *chartInstanceVoid, void *c8_inData);
static void c8_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_V_init_out, const char_T *c8_identifier,
  real_T c8_y[30]);
static void c8_b_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  real_T c8_y[30]);
static void c8_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_b_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static void c8_c_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_u_buff_out, const char_T *c8_identifier,
  real_T c8_y[2]);
static void c8_d_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  real_T c8_y[2]);
static void c8_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_c_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static real_T c8_e_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_J_star, const char_T *c8_identifier);
static real_T c8_f_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_d_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static const mxArray *c8_e_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static const mxArray *c8_f_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static const mxArray *c8_g_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static const mxArray *c8_h_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static const mxArray *c8_i_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static const mxArray *c8_j_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static void c8_g_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  real_T c8_y[30]);
static void c8_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static void c8_h_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  real_T c8_y[8]);
static void c8_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static void c8_i_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  real_T c8_y[900]);
static void c8_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_k_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static void c8_info_helper(c8_ResolvedFunctionInfo c8_info[44]);
static void c8_eml_scalar_eg(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance);
static void c8_b_eml_scalar_eg(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance);
static void c8_c_eml_scalar_eg(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance);
static void c8_eml_xgemm(SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance,
  real_T c8_A[62], real_T c8_B[1860], real_T c8_C[30], real_T c8_b_C[30]);
static void c8_d_eml_scalar_eg(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance);
static void c8_b_eml_xgemm(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, real_T c8_A[30], real_T c8_B[900], real_T c8_C[30], real_T
  c8_b_C[30]);
static void c8_e_eml_scalar_eg(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance);
static void c8_f_eml_scalar_eg(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance);
static void c8_g_eml_scalar_eg(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance);
static void c8_c_eml_xgemm(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, real_T c8_A[900], real_T c8_B[30], real_T c8_C[30], real_T
  c8_b_C[30]);
static void c8_h_eml_scalar_eg(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance);
static void c8_i_eml_scalar_eg(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance);
static void c8_j_eml_scalar_eg(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance);
static const mxArray *c8_l_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static int32_T c8_j_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static uint8_T c8_k_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_b_is_active_c8_Hquad_control_LIB_MPC, const
  char_T *c8_identifier);
static uint8_T c8_l_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_d_eml_xgemm(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, real_T c8_A[62], real_T c8_B[1860], real_T c8_C[30]);
static void c8_e_eml_xgemm(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, real_T c8_A[30], real_T c8_B[900], real_T c8_C[30]);
static void c8_f_eml_xgemm(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, real_T c8_A[900], real_T c8_B[30], real_T c8_C[30]);
static void init_dsm_address_info(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c8_Hquad_control_LIB_MPC
  (SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance)
{
  chartInstance->c8_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c8_is_active_c8_Hquad_control_LIB_MPC = 0U;
}

static void initialize_params_c8_Hquad_control_LIB_MPC
  (SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance)
{
}

static void enable_c8_Hquad_control_LIB_MPC
  (SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c8_Hquad_control_LIB_MPC
  (SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c8_update_debugger_state_c8_Hquad_control_LIB_MPC
  (SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c8_Hquad_control_LIB_MPC
  (SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance)
{
  const mxArray *c8_st;
  const mxArray *c8_y = NULL;
  real_T c8_hoistedGlobal;
  real_T c8_u;
  const mxArray *c8_b_y = NULL;
  int32_T c8_i0;
  real_T c8_b_u[30];
  const mxArray *c8_c_y = NULL;
  int32_T c8_i1;
  real_T c8_c_u[2];
  const mxArray *c8_d_y = NULL;
  real_T c8_b_hoistedGlobal;
  real_T c8_d_u;
  const mxArray *c8_e_y = NULL;
  uint8_T c8_c_hoistedGlobal;
  uint8_T c8_e_u;
  const mxArray *c8_f_y = NULL;
  real_T *c8_J_star;
  real_T *c8_u_opt;
  real_T (*c8_u_buff_out)[2];
  real_T (*c8_V_init_out)[30];
  c8_V_init_out = (real_T (*)[30])ssGetOutputPortSignal(chartInstance->S, 4);
  c8_u_buff_out = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
  c8_J_star = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c8_u_opt = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c8_st = NULL;
  c8_st = NULL;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_createcellarray(5), FALSE);
  c8_hoistedGlobal = *c8_J_star;
  c8_u = c8_hoistedGlobal;
  c8_b_y = NULL;
  sf_mex_assign(&c8_b_y, sf_mex_create("y", &c8_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c8_y, 0, c8_b_y);
  for (c8_i0 = 0; c8_i0 < 30; c8_i0++) {
    c8_b_u[c8_i0] = (*c8_V_init_out)[c8_i0];
  }

  c8_c_y = NULL;
  sf_mex_assign(&c8_c_y, sf_mex_create("y", c8_b_u, 0, 0U, 1U, 0U, 1, 30), FALSE);
  sf_mex_setcell(c8_y, 1, c8_c_y);
  for (c8_i1 = 0; c8_i1 < 2; c8_i1++) {
    c8_c_u[c8_i1] = (*c8_u_buff_out)[c8_i1];
  }

  c8_d_y = NULL;
  sf_mex_assign(&c8_d_y, sf_mex_create("y", c8_c_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_setcell(c8_y, 2, c8_d_y);
  c8_b_hoistedGlobal = *c8_u_opt;
  c8_d_u = c8_b_hoistedGlobal;
  c8_e_y = NULL;
  sf_mex_assign(&c8_e_y, sf_mex_create("y", &c8_d_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c8_y, 3, c8_e_y);
  c8_c_hoistedGlobal = chartInstance->c8_is_active_c8_Hquad_control_LIB_MPC;
  c8_e_u = c8_c_hoistedGlobal;
  c8_f_y = NULL;
  sf_mex_assign(&c8_f_y, sf_mex_create("y", &c8_e_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c8_y, 4, c8_f_y);
  sf_mex_assign(&c8_st, c8_y, FALSE);
  return c8_st;
}

static void set_sim_state_c8_Hquad_control_LIB_MPC
  (SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance, const mxArray *c8_st)
{
  const mxArray *c8_u;
  real_T c8_dv0[30];
  int32_T c8_i2;
  real_T c8_dv1[2];
  int32_T c8_i3;
  real_T *c8_J_star;
  real_T *c8_u_opt;
  real_T (*c8_V_init_out)[30];
  real_T (*c8_u_buff_out)[2];
  c8_V_init_out = (real_T (*)[30])ssGetOutputPortSignal(chartInstance->S, 4);
  c8_u_buff_out = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
  c8_J_star = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c8_u_opt = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c8_doneDoubleBufferReInit = TRUE;
  c8_u = sf_mex_dup(c8_st);
  *c8_J_star = c8_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c8_u, 0)), "J_star");
  c8_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 1)),
                      "V_init_out", c8_dv0);
  for (c8_i2 = 0; c8_i2 < 30; c8_i2++) {
    (*c8_V_init_out)[c8_i2] = c8_dv0[c8_i2];
  }

  c8_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 2)),
                        "u_buff_out", c8_dv1);
  for (c8_i3 = 0; c8_i3 < 2; c8_i3++) {
    (*c8_u_buff_out)[c8_i3] = c8_dv1[c8_i3];
  }

  *c8_u_opt = c8_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c8_u, 3)), "u_opt");
  chartInstance->c8_is_active_c8_Hquad_control_LIB_MPC = c8_k_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 4)),
     "is_active_c8_Hquad_control_LIB_MPC");
  sf_mex_destroy(&c8_u);
  c8_update_debugger_state_c8_Hquad_control_LIB_MPC(chartInstance);
  sf_mex_destroy(&c8_st);
}

static void finalize_c8_Hquad_control_LIB_MPC
  (SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance)
{
}

static void sf_c8_Hquad_control_LIB_MPC(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance)
{
  int32_T c8_i4;
  int32_T c8_i5;
  int32_T c8_i6;
  int32_T c8_i7;
  int32_T c8_i8;
  int32_T c8_i9;
  int32_T c8_i10;
  int32_T c8_i11;
  int32_T c8_i12;
  int32_T c8_i13;
  int32_T c8_i14;
  int32_T c8_i15;
  int32_T c8_i16;
  int32_T c8_i17;
  int32_T c8_i18;
  int32_T c8_i19;
  real_T *c8_u_opt;
  real_T *c8_J_star;
  real_T *c8_i_min;
  real_T *c8_L;
  real_T (*c8_V_init)[30];
  real_T (*c8_u_buff)[2];
  real_T (*c8_betas)[8];
  real_T (*c8_V_max)[30];
  real_T (*c8_X_ref)[62];
  real_T (*c8_x)[2];
  real_T (*c8_BB_delay)[4];
  real_T (*c8_AA_delay)[4];
  real_T (*c8_PP)[900];
  real_T (*c8_MM)[4];
  real_T (*c8_V_init_out)[30];
  real_T (*c8_u_buff_out)[2];
  real_T (*c8_LL_U_ref_PP)[900];
  real_T (*c8_LL_ref_PP)[1860];
  real_T (*c8_LL_PP)[60];
  real_T (*c8_TT_PP)[900];
  c8_V_init = (real_T (*)[30])ssGetInputPortSignal(chartInstance->S, 15);
  c8_u_buff = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 14);
  c8_L = (real_T *)ssGetInputPortSignal(chartInstance->S, 13);
  c8_betas = (real_T (*)[8])ssGetInputPortSignal(chartInstance->S, 12);
  c8_i_min = (real_T *)ssGetInputPortSignal(chartInstance->S, 11);
  c8_V_max = (real_T (*)[30])ssGetInputPortSignal(chartInstance->S, 10);
  c8_X_ref = (real_T (*)[62])ssGetInputPortSignal(chartInstance->S, 9);
  c8_x = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 8);
  c8_BB_delay = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 7);
  c8_AA_delay = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 6);
  c8_PP = (real_T (*)[900])ssGetInputPortSignal(chartInstance->S, 5);
  c8_MM = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 4);
  c8_V_init_out = (real_T (*)[30])ssGetOutputPortSignal(chartInstance->S, 4);
  c8_u_buff_out = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
  c8_J_star = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c8_LL_U_ref_PP = (real_T (*)[900])ssGetInputPortSignal(chartInstance->S, 3);
  c8_LL_ref_PP = (real_T (*)[1860])ssGetInputPortSignal(chartInstance->S, 2);
  c8_LL_PP = (real_T (*)[60])ssGetInputPortSignal(chartInstance->S, 1);
  c8_u_opt = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c8_TT_PP = (real_T (*)[900])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 6U, chartInstance->c8_sfEvent);
  for (c8_i4 = 0; c8_i4 < 900; c8_i4++) {
    _SFD_DATA_RANGE_CHECK((*c8_TT_PP)[c8_i4], 0U);
  }

  _SFD_DATA_RANGE_CHECK(*c8_u_opt, 1U);
  for (c8_i5 = 0; c8_i5 < 60; c8_i5++) {
    _SFD_DATA_RANGE_CHECK((*c8_LL_PP)[c8_i5], 2U);
  }

  for (c8_i6 = 0; c8_i6 < 1860; c8_i6++) {
    _SFD_DATA_RANGE_CHECK((*c8_LL_ref_PP)[c8_i6], 3U);
  }

  for (c8_i7 = 0; c8_i7 < 900; c8_i7++) {
    _SFD_DATA_RANGE_CHECK((*c8_LL_U_ref_PP)[c8_i7], 4U);
  }

  _SFD_DATA_RANGE_CHECK(*c8_J_star, 5U);
  for (c8_i8 = 0; c8_i8 < 2; c8_i8++) {
    _SFD_DATA_RANGE_CHECK((*c8_u_buff_out)[c8_i8], 6U);
  }

  for (c8_i9 = 0; c8_i9 < 30; c8_i9++) {
    _SFD_DATA_RANGE_CHECK((*c8_V_init_out)[c8_i9], 7U);
  }

  for (c8_i10 = 0; c8_i10 < 4; c8_i10++) {
    _SFD_DATA_RANGE_CHECK((*c8_MM)[c8_i10], 8U);
  }

  for (c8_i11 = 0; c8_i11 < 900; c8_i11++) {
    _SFD_DATA_RANGE_CHECK((*c8_PP)[c8_i11], 9U);
  }

  for (c8_i12 = 0; c8_i12 < 4; c8_i12++) {
    _SFD_DATA_RANGE_CHECK((*c8_AA_delay)[c8_i12], 10U);
  }

  for (c8_i13 = 0; c8_i13 < 4; c8_i13++) {
    _SFD_DATA_RANGE_CHECK((*c8_BB_delay)[c8_i13], 11U);
  }

  for (c8_i14 = 0; c8_i14 < 2; c8_i14++) {
    _SFD_DATA_RANGE_CHECK((*c8_x)[c8_i14], 12U);
  }

  for (c8_i15 = 0; c8_i15 < 62; c8_i15++) {
    _SFD_DATA_RANGE_CHECK((*c8_X_ref)[c8_i15], 13U);
  }

  for (c8_i16 = 0; c8_i16 < 30; c8_i16++) {
    _SFD_DATA_RANGE_CHECK((*c8_V_max)[c8_i16], 14U);
  }

  _SFD_DATA_RANGE_CHECK(*c8_i_min, 15U);
  for (c8_i17 = 0; c8_i17 < 8; c8_i17++) {
    _SFD_DATA_RANGE_CHECK((*c8_betas)[c8_i17], 16U);
  }

  _SFD_DATA_RANGE_CHECK(*c8_L, 17U);
  for (c8_i18 = 0; c8_i18 < 2; c8_i18++) {
    _SFD_DATA_RANGE_CHECK((*c8_u_buff)[c8_i18], 18U);
  }

  for (c8_i19 = 0; c8_i19 < 30; c8_i19++) {
    _SFD_DATA_RANGE_CHECK((*c8_V_init)[c8_i19], 19U);
  }

  chartInstance->c8_sfEvent = CALL_EVENT;
  c8_chartstep_c8_Hquad_control_LIB_MPC(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_Hquad_control_LIB_MPCMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c8_chartstep_c8_Hquad_control_LIB_MPC
  (SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance)
{
  real_T c8_hoistedGlobal;
  real_T c8_b_hoistedGlobal;
  int32_T c8_i20;
  real_T c8_TT_PP[900];
  int32_T c8_i21;
  real_T c8_LL_PP[60];
  int32_T c8_i22;
  real_T c8_LL_ref_PP[1860];
  int32_T c8_i23;
  real_T c8_LL_U_ref_PP[900];
  int32_T c8_i24;
  real_T c8_MM[4];
  int32_T c8_i25;
  real_T c8_PP[900];
  int32_T c8_i26;
  real_T c8_AA_delay[4];
  int32_T c8_i27;
  real_T c8_BB_delay[4];
  int32_T c8_i28;
  real_T c8_x[2];
  int32_T c8_i29;
  real_T c8_X_ref[62];
  int32_T c8_i30;
  real_T c8_V_max[30];
  real_T c8_i_min;
  int32_T c8_i31;
  real_T c8_betas[8];
  real_T c8_L;
  int32_T c8_i32;
  real_T c8_u_buff[2];
  int32_T c8_i33;
  real_T c8_V_init[30];
  uint32_T c8_debug_family_var_map[31];
  real_T c8_m;
  real_T c8_delay_steps;
  real_T c8_N;
  real_T c8_x_predicted[2];
  real_T c8_U_ref[30];
  real_T c8_LL_PP_ref[30];
  real_T c8_MM_ref;
  real_T c8_V_star[30];
  real_T c8_U_star[30];
  real_T c8_nargin = 16.0;
  real_T c8_nargout = 4.0;
  real_T c8_u_opt;
  real_T c8_J_star;
  real_T c8_u_buff_out[2];
  real_T c8_V_init_out[30];
  int32_T c8_i34;
  real_T c8_a[4];
  int32_T c8_i35;
  real_T c8_b[2];
  int32_T c8_i36;
  real_T c8_y[2];
  int32_T c8_i37;
  int32_T c8_i38;
  int32_T c8_i39;
  int32_T c8_i40;
  int32_T c8_i41;
  real_T c8_b_y[2];
  int32_T c8_i42;
  int32_T c8_i43;
  int32_T c8_i44;
  int32_T c8_i45;
  int32_T c8_i46;
  real_T c8_b_a[2];
  int32_T c8_i47;
  real_T c8_b_b[60];
  int32_T c8_i48;
  int32_T c8_i49;
  real_T c8_c_y[30];
  int32_T c8_i50;
  int32_T c8_i51;
  real_T c8_c_a[62];
  int32_T c8_i52;
  real_T c8_c_b[1860];
  int32_T c8_i53;
  real_T c8_d_y[30];
  int32_T c8_i54;
  real_T c8_d_a[62];
  int32_T c8_i55;
  real_T c8_d_b[1860];
  int32_T c8_i56;
  real_T c8_e_b[900];
  int32_T c8_i57;
  real_T c8_dv2[30];
  int32_T c8_i58;
  real_T c8_e_y[30];
  int32_T c8_i59;
  real_T c8_dv3[30];
  int32_T c8_i60;
  real_T c8_f_b[900];
  int32_T c8_i61;
  int32_T c8_i62;
  int32_T c8_i63;
  int32_T c8_i64;
  int32_T c8_i65;
  real_T c8_f_y[2];
  int32_T c8_i66;
  int32_T c8_i67;
  int32_T c8_k;
  int32_T c8_b_k;
  int32_T c8_i68;
  real_T c8_b_TT_PP[900];
  int32_T c8_i69;
  real_T c8_b_LL_PP_ref[30];
  int32_T c8_i70;
  real_T c8_b_V_max[30];
  int32_T c8_i71;
  real_T c8_c_V_max[30];
  int32_T c8_i72;
  real_T c8_b_V_init[30];
  int32_T c8_i73;
  real_T c8_b_betas[8];
  real_T c8_unusedU0;
  real_T c8_b_V_star[30];
  real_T c8_b_J_star;
  int32_T c8_i74;
  int32_T c8_i75;
  int32_T c8_i76;
  int32_T c8_i77;
  int32_T c8_i78;
  int32_T c8_i79;
  real_T c8_dv4[900];
  int32_T c8_i80;
  real_T c8_dv5[30];
  int32_T c8_i81;
  real_T c8_dv6[900];
  int32_T c8_i82;
  real_T c8_dv7[30];
  int32_T c8_i83;
  int32_T c8_i84;
  int32_T c8_i85;
  real_T *c8_b_i_min;
  real_T *c8_b_L;
  real_T *c8_b_u_opt;
  real_T *c8_c_J_star;
  real_T (*c8_b_u_buff_out)[2];
  real_T (*c8_b_V_init_out)[30];
  real_T (*c8_c_V_init)[30];
  real_T (*c8_b_u_buff)[2];
  real_T (*c8_c_betas)[8];
  real_T (*c8_d_V_max)[30];
  real_T (*c8_b_X_ref)[62];
  real_T (*c8_b_x)[2];
  real_T (*c8_b_BB_delay)[4];
  real_T (*c8_b_AA_delay)[4];
  real_T (*c8_b_PP)[900];
  real_T (*c8_b_MM)[4];
  real_T (*c8_b_LL_U_ref_PP)[900];
  real_T (*c8_b_LL_ref_PP)[1860];
  real_T (*c8_b_LL_PP)[60];
  real_T (*c8_c_TT_PP)[900];
  c8_c_V_init = (real_T (*)[30])ssGetInputPortSignal(chartInstance->S, 15);
  c8_b_u_buff = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 14);
  c8_b_L = (real_T *)ssGetInputPortSignal(chartInstance->S, 13);
  c8_c_betas = (real_T (*)[8])ssGetInputPortSignal(chartInstance->S, 12);
  c8_b_i_min = (real_T *)ssGetInputPortSignal(chartInstance->S, 11);
  c8_d_V_max = (real_T (*)[30])ssGetInputPortSignal(chartInstance->S, 10);
  c8_b_X_ref = (real_T (*)[62])ssGetInputPortSignal(chartInstance->S, 9);
  c8_b_x = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 8);
  c8_b_BB_delay = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 7);
  c8_b_AA_delay = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 6);
  c8_b_PP = (real_T (*)[900])ssGetInputPortSignal(chartInstance->S, 5);
  c8_b_MM = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 4);
  c8_b_V_init_out = (real_T (*)[30])ssGetOutputPortSignal(chartInstance->S, 4);
  c8_b_u_buff_out = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
  c8_c_J_star = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c8_b_LL_U_ref_PP = (real_T (*)[900])ssGetInputPortSignal(chartInstance->S, 3);
  c8_b_LL_ref_PP = (real_T (*)[1860])ssGetInputPortSignal(chartInstance->S, 2);
  c8_b_LL_PP = (real_T (*)[60])ssGetInputPortSignal(chartInstance->S, 1);
  c8_b_u_opt = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c8_c_TT_PP = (real_T (*)[900])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 6U, chartInstance->c8_sfEvent);
  c8_hoistedGlobal = *c8_b_i_min;
  c8_b_hoistedGlobal = *c8_b_L;
  for (c8_i20 = 0; c8_i20 < 900; c8_i20++) {
    c8_TT_PP[c8_i20] = (*c8_c_TT_PP)[c8_i20];
  }

  for (c8_i21 = 0; c8_i21 < 60; c8_i21++) {
    c8_LL_PP[c8_i21] = (*c8_b_LL_PP)[c8_i21];
  }

  for (c8_i22 = 0; c8_i22 < 1860; c8_i22++) {
    c8_LL_ref_PP[c8_i22] = (*c8_b_LL_ref_PP)[c8_i22];
  }

  for (c8_i23 = 0; c8_i23 < 900; c8_i23++) {
    c8_LL_U_ref_PP[c8_i23] = (*c8_b_LL_U_ref_PP)[c8_i23];
  }

  for (c8_i24 = 0; c8_i24 < 4; c8_i24++) {
    c8_MM[c8_i24] = (*c8_b_MM)[c8_i24];
  }

  for (c8_i25 = 0; c8_i25 < 900; c8_i25++) {
    c8_PP[c8_i25] = (*c8_b_PP)[c8_i25];
  }

  for (c8_i26 = 0; c8_i26 < 4; c8_i26++) {
    c8_AA_delay[c8_i26] = (*c8_b_AA_delay)[c8_i26];
  }

  for (c8_i27 = 0; c8_i27 < 4; c8_i27++) {
    c8_BB_delay[c8_i27] = (*c8_b_BB_delay)[c8_i27];
  }

  for (c8_i28 = 0; c8_i28 < 2; c8_i28++) {
    c8_x[c8_i28] = (*c8_b_x)[c8_i28];
  }

  for (c8_i29 = 0; c8_i29 < 62; c8_i29++) {
    c8_X_ref[c8_i29] = (*c8_b_X_ref)[c8_i29];
  }

  for (c8_i30 = 0; c8_i30 < 30; c8_i30++) {
    c8_V_max[c8_i30] = (*c8_d_V_max)[c8_i30];
  }

  c8_i_min = c8_hoistedGlobal;
  for (c8_i31 = 0; c8_i31 < 8; c8_i31++) {
    c8_betas[c8_i31] = (*c8_c_betas)[c8_i31];
  }

  c8_L = c8_b_hoistedGlobal;
  for (c8_i32 = 0; c8_i32 < 2; c8_i32++) {
    c8_u_buff[c8_i32] = (*c8_b_u_buff)[c8_i32];
  }

  for (c8_i33 = 0; c8_i33 < 30; c8_i33++) {
    c8_V_init[c8_i33] = (*c8_c_V_init)[c8_i33];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 31U, 31U, c8_debug_family_names,
    c8_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c8_m, 0U, c8_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c8_delay_steps, 1U, c8_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c8_N, 2U, c8_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_x_predicted, 3U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_U_ref, 4U, c8_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_LL_PP_ref, 5U, c8_j_sf_marshallOut,
    c8_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_MM_ref, 6U, c8_c_sf_marshallOut,
    c8_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_V_star, 7U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_U_star, 8U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_nargin, 9U, c8_c_sf_marshallOut,
    c8_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_nargout, 10U, c8_c_sf_marshallOut,
    c8_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_TT_PP, 11U, c8_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_LL_PP, 12U, c8_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_LL_ref_PP, 13U, c8_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_LL_U_ref_PP, 14U, c8_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_MM, 15U, c8_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_PP, 16U, c8_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_AA_delay, 17U, c8_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_BB_delay, 18U, c8_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_x, 19U, c8_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_X_ref, 20U, c8_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_V_max, 21U, c8_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c8_i_min, 22U, c8_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_betas, 23U, c8_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c8_L, 24U, c8_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_u_buff, 25U, c8_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_V_init, 26U, c8_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_u_opt, 27U, c8_c_sf_marshallOut,
    c8_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_J_star, 28U, c8_c_sf_marshallOut,
    c8_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_u_buff_out, 29U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_V_init_out, 30U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 6);
  c8_m = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 7);
  c8_delay_steps = 2.0;
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 8);
  c8_N = 30.0;
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 11);
  CV_EML_IF(0, 1, 0, c8_delay_steps == 0.0);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 14);
  for (c8_i34 = 0; c8_i34 < 4; c8_i34++) {
    c8_a[c8_i34] = c8_AA_delay[c8_i34];
  }

  for (c8_i35 = 0; c8_i35 < 2; c8_i35++) {
    c8_b[c8_i35] = c8_x[c8_i35];
  }

  c8_eml_scalar_eg(chartInstance);
  c8_eml_scalar_eg(chartInstance);
  for (c8_i36 = 0; c8_i36 < 2; c8_i36++) {
    c8_y[c8_i36] = 0.0;
    c8_i37 = 0;
    for (c8_i38 = 0; c8_i38 < 2; c8_i38++) {
      c8_y[c8_i36] += c8_a[c8_i37 + c8_i36] * c8_b[c8_i38];
      c8_i37 += 2;
    }
  }

  for (c8_i39 = 0; c8_i39 < 4; c8_i39++) {
    c8_a[c8_i39] = c8_BB_delay[c8_i39];
  }

  for (c8_i40 = 0; c8_i40 < 2; c8_i40++) {
    c8_b[c8_i40] = c8_u_buff[c8_i40];
  }

  c8_eml_scalar_eg(chartInstance);
  c8_eml_scalar_eg(chartInstance);
  for (c8_i41 = 0; c8_i41 < 2; c8_i41++) {
    c8_b_y[c8_i41] = 0.0;
    c8_i42 = 0;
    for (c8_i43 = 0; c8_i43 < 2; c8_i43++) {
      c8_b_y[c8_i41] += c8_a[c8_i42 + c8_i41] * c8_b[c8_i43];
      c8_i42 += 2;
    }
  }

  for (c8_i44 = 0; c8_i44 < 2; c8_i44++) {
    c8_x_predicted[c8_i44] = c8_y[c8_i44] + c8_b_y[c8_i44];
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 18);
  for (c8_i45 = 0; c8_i45 < 30; c8_i45++) {
    c8_U_ref[c8_i45] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 21);
  for (c8_i46 = 0; c8_i46 < 2; c8_i46++) {
    c8_b_a[c8_i46] = c8_x_predicted[c8_i46];
  }

  for (c8_i47 = 0; c8_i47 < 60; c8_i47++) {
    c8_b_b[c8_i47] = c8_LL_PP[c8_i47];
  }

  c8_b_eml_scalar_eg(chartInstance);
  c8_b_eml_scalar_eg(chartInstance);
  c8_i48 = 0;
  for (c8_i49 = 0; c8_i49 < 30; c8_i49++) {
    c8_c_y[c8_i49] = 0.0;
    for (c8_i50 = 0; c8_i50 < 2; c8_i50++) {
      c8_c_y[c8_i49] += c8_b_a[c8_i50] * c8_b_b[c8_i50 + c8_i48];
    }

    c8_i48 += 2;
  }

  for (c8_i51 = 0; c8_i51 < 62; c8_i51++) {
    c8_c_a[c8_i51] = c8_X_ref[c8_i51];
  }

  for (c8_i52 = 0; c8_i52 < 1860; c8_i52++) {
    c8_c_b[c8_i52] = c8_LL_ref_PP[c8_i52];
  }

  c8_c_eml_scalar_eg(chartInstance);
  c8_c_eml_scalar_eg(chartInstance);
  for (c8_i53 = 0; c8_i53 < 30; c8_i53++) {
    c8_d_y[c8_i53] = 0.0;
  }

  for (c8_i54 = 0; c8_i54 < 62; c8_i54++) {
    c8_d_a[c8_i54] = c8_c_a[c8_i54];
  }

  for (c8_i55 = 0; c8_i55 < 1860; c8_i55++) {
    c8_d_b[c8_i55] = c8_c_b[c8_i55];
  }

  c8_d_eml_xgemm(chartInstance, c8_d_a, c8_d_b, c8_d_y);
  for (c8_i56 = 0; c8_i56 < 900; c8_i56++) {
    c8_e_b[c8_i56] = c8_LL_U_ref_PP[c8_i56];
  }

  c8_d_eml_scalar_eg(chartInstance);
  c8_d_eml_scalar_eg(chartInstance);
  for (c8_i57 = 0; c8_i57 < 30; c8_i57++) {
    c8_dv2[c8_i57] = 0.0;
  }

  for (c8_i58 = 0; c8_i58 < 30; c8_i58++) {
    c8_e_y[c8_i58] = 0.0;
  }

  for (c8_i59 = 0; c8_i59 < 30; c8_i59++) {
    c8_dv3[c8_i59] = c8_dv2[c8_i59];
  }

  for (c8_i60 = 0; c8_i60 < 900; c8_i60++) {
    c8_f_b[c8_i60] = c8_e_b[c8_i60];
  }

  c8_e_eml_xgemm(chartInstance, c8_dv3, c8_f_b, c8_e_y);
  for (c8_i61 = 0; c8_i61 < 30; c8_i61++) {
    c8_LL_PP_ref[c8_i61] = (c8_c_y[c8_i61] - c8_d_y[c8_i61]) - c8_e_y[c8_i61];
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 22);
  for (c8_i62 = 0; c8_i62 < 2; c8_i62++) {
    c8_b_a[c8_i62] = c8_x_predicted[c8_i62];
  }

  for (c8_i63 = 0; c8_i63 < 4; c8_i63++) {
    c8_a[c8_i63] = c8_MM[c8_i63];
  }

  c8_e_eml_scalar_eg(chartInstance);
  c8_e_eml_scalar_eg(chartInstance);
  c8_i64 = 0;
  for (c8_i65 = 0; c8_i65 < 2; c8_i65++) {
    c8_f_y[c8_i65] = 0.0;
    for (c8_i66 = 0; c8_i66 < 2; c8_i66++) {
      c8_f_y[c8_i65] += c8_b_a[c8_i66] * c8_a[c8_i66 + c8_i64];
    }

    c8_i64 += 2;
  }

  for (c8_i67 = 0; c8_i67 < 2; c8_i67++) {
    c8_b[c8_i67] = c8_x_predicted[c8_i67];
  }

  c8_f_eml_scalar_eg(chartInstance);
  c8_f_eml_scalar_eg(chartInstance);
  c8_MM_ref = 0.0;
  for (c8_k = 1; c8_k < 3; c8_k++) {
    c8_b_k = c8_k;
    c8_MM_ref += c8_f_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c8_b_k), 1, 2, 1, 0) - 1] *
      c8_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c8_b_k), 1, 2, 1, 0) - 1];
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 25);
  for (c8_i68 = 0; c8_i68 < 900; c8_i68++) {
    c8_b_TT_PP[c8_i68] = c8_TT_PP[c8_i68];
  }

  for (c8_i69 = 0; c8_i69 < 30; c8_i69++) {
    c8_b_LL_PP_ref[c8_i69] = c8_LL_PP_ref[c8_i69];
  }

  for (c8_i70 = 0; c8_i70 < 30; c8_i70++) {
    c8_b_V_max[c8_i70] = -c8_V_max[c8_i70];
  }

  for (c8_i71 = 0; c8_i71 < 30; c8_i71++) {
    c8_c_V_max[c8_i71] = c8_V_max[c8_i71];
  }

  for (c8_i72 = 0; c8_i72 < 30; c8_i72++) {
    c8_b_V_init[c8_i72] = c8_V_init[c8_i72];
  }

  for (c8_i73 = 0; c8_i73 < 8; c8_i73++) {
    c8_b_betas[c8_i73] = c8_betas[c8_i73];
  }

  c8_runFastGradient(chartInstance, c8_b_TT_PP, c8_b_LL_PP_ref, c8_MM_ref,
                     c8_b_V_max, c8_c_V_max, c8_b_V_init, c8_i_min, c8_b_betas,
                     c8_L, &c8_b_J_star, c8_b_V_star, &c8_unusedU0);
  c8_J_star = c8_b_J_star;
  for (c8_i74 = 0; c8_i74 < 30; c8_i74++) {
    c8_V_star[c8_i74] = c8_b_V_star[c8_i74];
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 25);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 32);
  for (c8_i75 = 0; c8_i75 < 900; c8_i75++) {
    c8_e_b[c8_i75] = c8_PP[c8_i75];
  }

  for (c8_i76 = 0; c8_i76 < 30; c8_i76++) {
    c8_b_V_star[c8_i76] = c8_V_star[c8_i76];
  }

  c8_g_eml_scalar_eg(chartInstance);
  c8_g_eml_scalar_eg(chartInstance);
  for (c8_i77 = 0; c8_i77 < 30; c8_i77++) {
    c8_U_star[c8_i77] = 0.0;
  }

  for (c8_i78 = 0; c8_i78 < 30; c8_i78++) {
    c8_U_star[c8_i78] = 0.0;
  }

  for (c8_i79 = 0; c8_i79 < 900; c8_i79++) {
    c8_dv4[c8_i79] = c8_e_b[c8_i79];
  }

  for (c8_i80 = 0; c8_i80 < 30; c8_i80++) {
    c8_dv5[c8_i80] = c8_b_V_star[c8_i80];
  }

  for (c8_i81 = 0; c8_i81 < 900; c8_i81++) {
    c8_dv6[c8_i81] = c8_dv4[c8_i81];
  }

  for (c8_i82 = 0; c8_i82 < 30; c8_i82++) {
    c8_dv7[c8_i82] = c8_dv5[c8_i82];
  }

  c8_f_eml_xgemm(chartInstance, c8_dv6, c8_dv7, c8_U_star);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 35);
  CV_EML_IF(0, 1, 1, c8_delay_steps == 0.0);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 38);
  c8_u_buff_out[0] = c8_u_buff[1];
  c8_u_buff_out[1] = c8_U_star[0];
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 42);
  for (c8_i83 = 0; c8_i83 < 29; c8_i83++) {
    c8_V_init_out[c8_i83] = c8_V_star[c8_i83 + 1];
  }

  c8_V_init_out[29] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 44);
  c8_u_opt = c8_U_star[0];
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, -44);
  _SFD_SYMBOL_SCOPE_POP();
  *c8_b_u_opt = c8_u_opt;
  *c8_c_J_star = c8_J_star;
  for (c8_i84 = 0; c8_i84 < 2; c8_i84++) {
    (*c8_b_u_buff_out)[c8_i84] = c8_u_buff_out[c8_i84];
  }

  for (c8_i85 = 0; c8_i85 < 30; c8_i85++) {
    (*c8_b_V_init_out)[c8_i85] = c8_V_init_out[c8_i85];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c8_sfEvent);
}

static void initSimStructsc8_Hquad_control_LIB_MPC
  (SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance)
{
}

static void registerMessagesc8_Hquad_control_LIB_MPC
  (SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance)
{
}

static void c8_runFastGradient(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, real_T c8_TT_PP[900], real_T c8_LL_PP[30], real_T c8_MM,
  real_T c8_V_min[30], real_T c8_V_max[30], real_T c8_V_init[30], real_T
  c8_i_min, real_T c8_betas[8], real_T c8_L, real_T *c8_J, real_T c8_V[30],
  real_T *c8_actual_num_iters)
{
  uint32_T c8_debug_family_var_map[23];
  real_T c8_MONITOR;
  real_T c8_L_inv;
  real_T c8_LL_PP_t[30];
  real_T c8_V_i[30];
  real_T c8_W_i[30];
  real_T c8_i;
  real_T c8_V_ip1[30];
  real_T c8_W_ip1[30];
  real_T c8_nargin = 10.0;
  real_T c8_nargout = 3.0;
  real_T c8_B;
  real_T c8_y;
  real_T c8_b_y;
  int32_T c8_i86;
  int32_T c8_i87;
  real_T c8_a[900];
  int32_T c8_i88;
  real_T c8_b[30];
  int32_T c8_i89;
  real_T c8_c_y[30];
  int32_T c8_i90;
  real_T c8_b_a[900];
  int32_T c8_i91;
  real_T c8_b_b[30];
  real_T c8_c_a;
  int32_T c8_i92;
  int32_T c8_i93;
  int32_T c8_i94;
  int32_T c8_i95;
  int32_T c8_k;
  int32_T c8_b_k;
  real_T c8_xk;
  real_T c8_yk;
  real_T c8_x;
  real_T c8_d_y;
  real_T c8_extremum;
  real_T c8_minval[30];
  int32_T c8_i96;
  int32_T c8_c_k;
  int32_T c8_d_k;
  real_T c8_b_xk;
  real_T c8_b_yk;
  real_T c8_b_x;
  real_T c8_e_y;
  real_T c8_b_extremum;
  int32_T c8_i97;
  real_T c8_b_i_min;
  int32_T c8_i98;
  int32_T c8_b_i;
  int32_T c8_i99;
  int32_T c8_i100;
  int32_T c8_i101;
  int32_T c8_i102;
  real_T c8_d_a[900];
  int32_T c8_i103;
  real_T c8_c_b[30];
  real_T c8_e_a;
  int32_T c8_i104;
  int32_T c8_i105;
  int32_T c8_i106;
  int32_T c8_i107;
  int32_T c8_e_k;
  int32_T c8_f_k;
  real_T c8_c_xk;
  real_T c8_c_yk;
  real_T c8_c_x;
  real_T c8_f_y;
  real_T c8_c_extremum;
  int32_T c8_i108;
  int32_T c8_g_k;
  int32_T c8_h_k;
  real_T c8_d_xk;
  real_T c8_d_yk;
  real_T c8_d_x;
  real_T c8_g_y;
  real_T c8_d_extremum;
  real_T c8_f_a;
  int32_T c8_i109;
  int32_T c8_i110;
  int32_T c8_i111;
  int32_T c8_i112;
  int32_T c8_i113;
  int32_T c8_i114;
  int32_T c8_i115;
  real_T c8_d_b[30];
  int32_T c8_i116;
  int32_T c8_i117;
  int32_T c8_i118;
  real_T c8_h_y[30];
  int32_T c8_i119;
  real_T c8_e_b[30];
  int32_T c8_i120;
  real_T c8_g_a[900];
  int32_T c8_i121;
  real_T c8_i_y;
  int32_T c8_i_k;
  int32_T c8_j_k;
  int32_T c8_i122;
  int32_T c8_i123;
  real_T c8_j_y;
  int32_T c8_k_k;
  int32_T c8_l_k;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 23U, 23U, c8_b_debug_family_names,
    c8_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c8_MONITOR, 0U, c8_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_L_inv, 1U, c8_c_sf_marshallOut,
    c8_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_LL_PP_t, 2U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_V_i, 3U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_W_i, 4U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_i, 5U, c8_c_sf_marshallOut,
    c8_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_V_ip1, 6U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_W_ip1, 7U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(NULL, 8U, c8_k_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_nargin, 9U, c8_c_sf_marshallOut,
    c8_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_nargout, 10U, c8_c_sf_marshallOut,
    c8_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_TT_PP, 11U, c8_g_sf_marshallOut,
    c8_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_LL_PP, 12U, c8_j_sf_marshallOut,
    c8_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_MM, 13U, c8_c_sf_marshallOut,
    c8_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_V_min, 14U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_V_max, 15U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_V_init, 16U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_i_min, 17U, c8_c_sf_marshallOut,
    c8_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_betas, 18U, c8_d_sf_marshallOut,
    c8_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_L, 19U, c8_c_sf_marshallOut,
    c8_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_J, 20U, c8_c_sf_marshallOut,
    c8_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_V, 21U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_actual_num_iters, 22U,
    c8_c_sf_marshallOut, c8_c_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c8_sfEvent, 33);
  c8_MONITOR = 0.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c8_sfEvent, 34);
  *c8_actual_num_iters = rtInf;
  _SFD_SCRIPT_CALL(0U, chartInstance->c8_sfEvent, 35);
  CV_SCRIPT_COND(0, 0, TRUE);
  CV_SCRIPT_MCDC(0, 0, FALSE);
  CV_SCRIPT_IF(0, 0, FALSE);
  _SFD_SCRIPT_CALL(0U, chartInstance->c8_sfEvent, 41);
  c8_B = c8_L;
  c8_y = c8_B;
  c8_b_y = c8_y;
  c8_L_inv = 1.0 / c8_b_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c8_sfEvent, 42);
  for (c8_i86 = 0; c8_i86 < 30; c8_i86++) {
    c8_LL_PP_t[c8_i86] = c8_LL_PP[c8_i86];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c8_sfEvent, 44);
  for (c8_i87 = 0; c8_i87 < 900; c8_i87++) {
    c8_a[c8_i87] = c8_TT_PP[c8_i87];
  }

  for (c8_i88 = 0; c8_i88 < 30; c8_i88++) {
    c8_b[c8_i88] = c8_V_init[c8_i88];
  }

  c8_g_eml_scalar_eg(chartInstance);
  c8_g_eml_scalar_eg(chartInstance);
  for (c8_i89 = 0; c8_i89 < 30; c8_i89++) {
    c8_c_y[c8_i89] = 0.0;
  }

  for (c8_i90 = 0; c8_i90 < 900; c8_i90++) {
    c8_b_a[c8_i90] = c8_a[c8_i90];
  }

  for (c8_i91 = 0; c8_i91 < 30; c8_i91++) {
    c8_b_b[c8_i91] = c8_b[c8_i91];
  }

  c8_f_eml_xgemm(chartInstance, c8_b_a, c8_b_b, c8_c_y);
  c8_c_a = c8_L_inv;
  for (c8_i92 = 0; c8_i92 < 30; c8_i92++) {
    c8_c_y[c8_i92] += c8_LL_PP_t[c8_i92];
  }

  for (c8_i93 = 0; c8_i93 < 30; c8_i93++) {
    c8_c_y[c8_i93] *= c8_c_a;
  }

  for (c8_i94 = 0; c8_i94 < 30; c8_i94++) {
    c8_b[c8_i94] = c8_V_max[c8_i94];
  }

  for (c8_i95 = 0; c8_i95 < 30; c8_i95++) {
    c8_c_y[c8_i95] = c8_V_init[c8_i95] - c8_c_y[c8_i95];
  }

  c8_h_eml_scalar_eg(chartInstance);
  for (c8_k = 1; c8_k < 31; c8_k++) {
    c8_b_k = c8_k;
    c8_xk = c8_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c8_b_k), 1, 30, 1, 0) - 1];
    c8_yk = c8_c_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
      "", (real_T)c8_b_k), 1, 30, 1, 0) - 1];
    c8_x = c8_xk;
    c8_d_y = c8_yk;
    c8_i_eml_scalar_eg(chartInstance);
    c8_extremum = muDoubleScalarMin(c8_x, c8_d_y);
    c8_minval[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c8_b_k), 1, 30, 1, 0) - 1] = c8_extremum;
  }

  for (c8_i96 = 0; c8_i96 < 30; c8_i96++) {
    c8_b[c8_i96] = c8_V_min[c8_i96];
  }

  c8_h_eml_scalar_eg(chartInstance);
  for (c8_c_k = 1; c8_c_k < 31; c8_c_k++) {
    c8_d_k = c8_c_k;
    c8_b_xk = c8_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
      "", (real_T)c8_d_k), 1, 30, 1, 0) - 1];
    c8_b_yk = c8_minval[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c8_d_k), 1, 30, 1, 0) - 1];
    c8_b_x = c8_b_xk;
    c8_e_y = c8_b_yk;
    c8_i_eml_scalar_eg(chartInstance);
    c8_b_extremum = muDoubleScalarMax(c8_b_x, c8_e_y);
    c8_V_i[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c8_d_k), 1, 30, 1, 0) - 1] = c8_b_extremum;
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c8_sfEvent, 45);
  for (c8_i97 = 0; c8_i97 < 30; c8_i97++) {
    c8_W_i[c8_i97] = c8_V_i[c8_i97];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c8_sfEvent, 47);
  CV_SCRIPT_IF(0, 1, c8_MONITOR != 0.0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c8_sfEvent, 58);
  c8_b_i_min = c8_i_min;
  c8_i98 = (int32_T)c8_b_i_min;
  _SFD_FOR_LOOP_VECTOR_CHECK(1.0, 1.0, c8_b_i_min, mxDOUBLE_CLASS, c8_i98);
  c8_i = 1.0;
  c8_b_i = 0;
  while (c8_b_i <= c8_i98 - 1) {
    c8_i = 1.0 + (real_T)c8_b_i;
    CV_SCRIPT_FOR(0, 0, 1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c8_sfEvent, 59);
    for (c8_i99 = 0; c8_i99 < 900; c8_i99++) {
      c8_a[c8_i99] = c8_TT_PP[c8_i99];
    }

    for (c8_i100 = 0; c8_i100 < 30; c8_i100++) {
      c8_b[c8_i100] = c8_W_i[c8_i100];
    }

    c8_g_eml_scalar_eg(chartInstance);
    c8_g_eml_scalar_eg(chartInstance);
    for (c8_i101 = 0; c8_i101 < 30; c8_i101++) {
      c8_c_y[c8_i101] = 0.0;
    }

    for (c8_i102 = 0; c8_i102 < 900; c8_i102++) {
      c8_d_a[c8_i102] = c8_a[c8_i102];
    }

    for (c8_i103 = 0; c8_i103 < 30; c8_i103++) {
      c8_c_b[c8_i103] = c8_b[c8_i103];
    }

    c8_f_eml_xgemm(chartInstance, c8_d_a, c8_c_b, c8_c_y);
    c8_e_a = c8_L_inv;
    for (c8_i104 = 0; c8_i104 < 30; c8_i104++) {
      c8_c_y[c8_i104] += c8_LL_PP_t[c8_i104];
    }

    for (c8_i105 = 0; c8_i105 < 30; c8_i105++) {
      c8_c_y[c8_i105] *= c8_e_a;
    }

    for (c8_i106 = 0; c8_i106 < 30; c8_i106++) {
      c8_b[c8_i106] = c8_V_max[c8_i106];
    }

    for (c8_i107 = 0; c8_i107 < 30; c8_i107++) {
      c8_c_y[c8_i107] = c8_W_i[c8_i107] - c8_c_y[c8_i107];
    }

    c8_h_eml_scalar_eg(chartInstance);
    for (c8_e_k = 1; c8_e_k < 31; c8_e_k++) {
      c8_f_k = c8_e_k;
      c8_c_xk = c8_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
        ("", (real_T)c8_f_k), 1, 30, 1, 0) - 1];
      c8_c_yk = c8_c_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c8_f_k), 1, 30, 1, 0) - 1];
      c8_c_x = c8_c_xk;
      c8_f_y = c8_c_yk;
      c8_i_eml_scalar_eg(chartInstance);
      c8_c_extremum = muDoubleScalarMin(c8_c_x, c8_f_y);
      c8_minval[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c8_f_k), 1, 30, 1, 0) - 1] = c8_c_extremum;
    }

    for (c8_i108 = 0; c8_i108 < 30; c8_i108++) {
      c8_b[c8_i108] = c8_V_min[c8_i108];
    }

    c8_h_eml_scalar_eg(chartInstance);
    for (c8_g_k = 1; c8_g_k < 31; c8_g_k++) {
      c8_h_k = c8_g_k;
      c8_d_xk = c8_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
        ("", (real_T)c8_h_k), 1, 30, 1, 0) - 1];
      c8_d_yk = c8_minval[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c8_h_k), 1, 30, 1, 0) - 1];
      c8_d_x = c8_d_xk;
      c8_g_y = c8_d_yk;
      c8_i_eml_scalar_eg(chartInstance);
      c8_d_extremum = muDoubleScalarMax(c8_d_x, c8_g_y);
      c8_V_ip1[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c8_h_k), 1, 30, 1, 0) - 1] = c8_d_extremum;
    }

    _SFD_SCRIPT_CALL(0U, chartInstance->c8_sfEvent, 62);
    c8_f_a = c8_betas[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("betas",
      (int32_T)_SFD_INTEGER_CHECK("i", c8_i), 1, 8, 1, 0) - 1];
    for (c8_i109 = 0; c8_i109 < 30; c8_i109++) {
      c8_b[c8_i109] = c8_V_ip1[c8_i109] - c8_V_i[c8_i109];
    }

    for (c8_i110 = 0; c8_i110 < 30; c8_i110++) {
      c8_b[c8_i110] *= c8_f_a;
    }

    for (c8_i111 = 0; c8_i111 < 30; c8_i111++) {
      c8_W_ip1[c8_i111] = c8_V_ip1[c8_i111] + c8_b[c8_i111];
    }

    _SFD_SCRIPT_CALL(0U, chartInstance->c8_sfEvent, 64);
    for (c8_i112 = 0; c8_i112 < 30; c8_i112++) {
      c8_V_i[c8_i112] = c8_V_ip1[c8_i112];
    }

    _SFD_SCRIPT_CALL(0U, chartInstance->c8_sfEvent, 65);
    for (c8_i113 = 0; c8_i113 < 30; c8_i113++) {
      c8_W_i[c8_i113] = c8_W_ip1[c8_i113];
    }

    _SFD_SCRIPT_CALL(0U, chartInstance->c8_sfEvent, 67);
    CV_SCRIPT_IF(0, 3, c8_MONITOR != 0.0);
    c8_b_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_SCRIPT_FOR(0, 0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c8_sfEvent, 80);
  for (c8_i114 = 0; c8_i114 < 30; c8_i114++) {
    c8_V[c8_i114] = c8_V_i[c8_i114];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c8_sfEvent, 81);
  for (c8_i115 = 0; c8_i115 < 30; c8_i115++) {
    c8_d_b[c8_i115] = c8_V_i[c8_i115];
  }

  for (c8_i116 = 0; c8_i116 < 30; c8_i116++) {
    c8_d_b[c8_i116] *= 0.5;
  }

  for (c8_i117 = 0; c8_i117 < 900; c8_i117++) {
    c8_a[c8_i117] = c8_TT_PP[c8_i117];
  }

  c8_d_eml_scalar_eg(chartInstance);
  c8_d_eml_scalar_eg(chartInstance);
  for (c8_i118 = 0; c8_i118 < 30; c8_i118++) {
    c8_h_y[c8_i118] = 0.0;
  }

  for (c8_i119 = 0; c8_i119 < 30; c8_i119++) {
    c8_e_b[c8_i119] = c8_d_b[c8_i119];
  }

  for (c8_i120 = 0; c8_i120 < 900; c8_i120++) {
    c8_g_a[c8_i120] = c8_a[c8_i120];
  }

  c8_e_eml_xgemm(chartInstance, c8_e_b, c8_g_a, c8_h_y);
  for (c8_i121 = 0; c8_i121 < 30; c8_i121++) {
    c8_b[c8_i121] = c8_V_i[c8_i121];
  }

  c8_j_eml_scalar_eg(chartInstance);
  c8_j_eml_scalar_eg(chartInstance);
  c8_i_y = 0.0;
  for (c8_i_k = 1; c8_i_k < 31; c8_i_k++) {
    c8_j_k = c8_i_k;
    c8_i_y += c8_h_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
      ("", (real_T)c8_j_k), 1, 30, 1, 0) - 1] * c8_b[_SFD_EML_ARRAY_BOUNDS_CHECK
      ("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c8_j_k), 1, 30, 1, 0) - 1];
  }

  for (c8_i122 = 0; c8_i122 < 30; c8_i122++) {
    c8_d_b[c8_i122] = c8_LL_PP[c8_i122];
  }

  for (c8_i123 = 0; c8_i123 < 30; c8_i123++) {
    c8_b[c8_i123] = c8_V_i[c8_i123];
  }

  c8_j_eml_scalar_eg(chartInstance);
  c8_j_eml_scalar_eg(chartInstance);
  c8_j_y = 0.0;
  for (c8_k_k = 1; c8_k_k < 31; c8_k_k++) {
    c8_l_k = c8_k_k;
    c8_j_y += c8_d_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
      ("", (real_T)c8_l_k), 1, 30, 1, 0) - 1] * c8_b[_SFD_EML_ARRAY_BOUNDS_CHECK
      ("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c8_l_k), 1, 30, 1, 0) - 1];
  }

  *c8_J = (c8_i_y + c8_j_y) + c8_MM;
  _SFD_SCRIPT_CALL(0U, chartInstance->c8_sfEvent, 82);
  CV_SCRIPT_IF(0, 5, CV_SCRIPT_MCDC(0, 1, !(CV_SCRIPT_COND(0, 1, c8_MONITOR !=
    0.0) != 0.0)));
  _SFD_SCRIPT_CALL(0U, chartInstance->c8_sfEvent, 83);
  *c8_actual_num_iters = c8_i_min;
  _SFD_SCRIPT_CALL(0U, chartInstance->c8_sfEvent, -83);
  _SFD_SYMBOL_SCOPE_POP();
}

static void init_script_number_translation(uint32_T c8_machineNumber, uint32_T
  c8_chartNumber)
{
  _SFD_SCRIPT_TRANSLATION(c8_chartNumber, 0U, sf_debug_get_script_id(
    "/home/darivianos/Matlab/MPC_FastGradient/tools/runFastGradient.m"));
}

static const mxArray *c8_sf_marshallOut(void *chartInstanceVoid, void *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_i124;
  real_T c8_b_inData[30];
  int32_T c8_i125;
  real_T c8_u[30];
  const mxArray *c8_y = NULL;
  SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc8_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  for (c8_i124 = 0; c8_i124 < 30; c8_i124++) {
    c8_b_inData[c8_i124] = (*(real_T (*)[30])c8_inData)[c8_i124];
  }

  for (c8_i125 = 0; c8_i125 < 30; c8_i125++) {
    c8_u[c8_i125] = c8_b_inData[c8_i125];
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 1, 30), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static void c8_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_V_init_out, const char_T *c8_identifier,
  real_T c8_y[30])
{
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_V_init_out), &c8_thisId,
                        c8_y);
  sf_mex_destroy(&c8_V_init_out);
}

static void c8_b_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  real_T c8_y[30])
{
  real_T c8_dv8[30];
  int32_T c8_i126;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), c8_dv8, 1, 0, 0U, 1, 0U, 1, 30);
  for (c8_i126 = 0; c8_i126 < 30; c8_i126++) {
    c8_y[c8_i126] = c8_dv8[c8_i126];
  }

  sf_mex_destroy(&c8_u);
}

static void c8_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_V_init_out;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y[30];
  int32_T c8_i127;
  SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc8_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c8_V_init_out = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_V_init_out), &c8_thisId,
                        c8_y);
  sf_mex_destroy(&c8_V_init_out);
  for (c8_i127 = 0; c8_i127 < 30; c8_i127++) {
    (*(real_T (*)[30])c8_outData)[c8_i127] = c8_y[c8_i127];
  }

  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_b_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_i128;
  real_T c8_b_inData[2];
  int32_T c8_i129;
  real_T c8_u[2];
  const mxArray *c8_y = NULL;
  SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc8_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  for (c8_i128 = 0; c8_i128 < 2; c8_i128++) {
    c8_b_inData[c8_i128] = (*(real_T (*)[2])c8_inData)[c8_i128];
  }

  for (c8_i129 = 0; c8_i129 < 2; c8_i129++) {
    c8_u[c8_i129] = c8_b_inData[c8_i129];
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static void c8_c_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_u_buff_out, const char_T *c8_identifier,
  real_T c8_y[2])
{
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_u_buff_out), &c8_thisId,
                        c8_y);
  sf_mex_destroy(&c8_u_buff_out);
}

static void c8_d_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  real_T c8_y[2])
{
  real_T c8_dv9[2];
  int32_T c8_i130;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), c8_dv9, 1, 0, 0U, 1, 0U, 1, 2);
  for (c8_i130 = 0; c8_i130 < 2; c8_i130++) {
    c8_y[c8_i130] = c8_dv9[c8_i130];
  }

  sf_mex_destroy(&c8_u);
}

static void c8_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_u_buff_out;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y[2];
  int32_T c8_i131;
  SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc8_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c8_u_buff_out = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_u_buff_out), &c8_thisId,
                        c8_y);
  sf_mex_destroy(&c8_u_buff_out);
  for (c8_i131 = 0; c8_i131 < 2; c8_i131++) {
    (*(real_T (*)[2])c8_outData)[c8_i131] = c8_y[c8_i131];
  }

  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_c_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  real_T c8_u;
  const mxArray *c8_y = NULL;
  SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc8_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = *(real_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static real_T c8_e_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_J_star, const char_T *c8_identifier)
{
  real_T c8_y;
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_J_star), &c8_thisId);
  sf_mex_destroy(&c8_J_star);
  return c8_y;
}

static real_T c8_f_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  real_T c8_y;
  real_T c8_d0;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_d0, 1, 0, 0U, 0, 0U, 0);
  c8_y = c8_d0;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_J_star;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y;
  SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc8_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c8_J_star = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_J_star), &c8_thisId);
  sf_mex_destroy(&c8_J_star);
  *(real_T *)c8_outData = c8_y;
  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_d_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_i132;
  real_T c8_b_inData[8];
  int32_T c8_i133;
  real_T c8_u[8];
  const mxArray *c8_y = NULL;
  SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc8_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  for (c8_i132 = 0; c8_i132 < 8; c8_i132++) {
    c8_b_inData[c8_i132] = (*(real_T (*)[8])c8_inData)[c8_i132];
  }

  for (c8_i133 = 0; c8_i133 < 8; c8_i133++) {
    c8_u[c8_i133] = c8_b_inData[c8_i133];
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 1, 8), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static const mxArray *c8_e_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_i134;
  real_T c8_b_inData[62];
  int32_T c8_i135;
  real_T c8_u[62];
  const mxArray *c8_y = NULL;
  SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc8_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  for (c8_i134 = 0; c8_i134 < 62; c8_i134++) {
    c8_b_inData[c8_i134] = (*(real_T (*)[62])c8_inData)[c8_i134];
  }

  for (c8_i135 = 0; c8_i135 < 62; c8_i135++) {
    c8_u[c8_i135] = c8_b_inData[c8_i135];
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 1, 62), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static const mxArray *c8_f_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_i136;
  int32_T c8_i137;
  int32_T c8_i138;
  real_T c8_b_inData[4];
  int32_T c8_i139;
  int32_T c8_i140;
  int32_T c8_i141;
  real_T c8_u[4];
  const mxArray *c8_y = NULL;
  SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc8_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_i136 = 0;
  for (c8_i137 = 0; c8_i137 < 2; c8_i137++) {
    for (c8_i138 = 0; c8_i138 < 2; c8_i138++) {
      c8_b_inData[c8_i138 + c8_i136] = (*(real_T (*)[4])c8_inData)[c8_i138 +
        c8_i136];
    }

    c8_i136 += 2;
  }

  c8_i139 = 0;
  for (c8_i140 = 0; c8_i140 < 2; c8_i140++) {
    for (c8_i141 = 0; c8_i141 < 2; c8_i141++) {
      c8_u[c8_i141 + c8_i139] = c8_b_inData[c8_i141 + c8_i139];
    }

    c8_i139 += 2;
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 2, 2, 2), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static const mxArray *c8_g_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_i142;
  int32_T c8_i143;
  int32_T c8_i144;
  real_T c8_b_inData[900];
  int32_T c8_i145;
  int32_T c8_i146;
  int32_T c8_i147;
  real_T c8_u[900];
  const mxArray *c8_y = NULL;
  SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc8_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_i142 = 0;
  for (c8_i143 = 0; c8_i143 < 30; c8_i143++) {
    for (c8_i144 = 0; c8_i144 < 30; c8_i144++) {
      c8_b_inData[c8_i144 + c8_i142] = (*(real_T (*)[900])c8_inData)[c8_i144 +
        c8_i142];
    }

    c8_i142 += 30;
  }

  c8_i145 = 0;
  for (c8_i146 = 0; c8_i146 < 30; c8_i146++) {
    for (c8_i147 = 0; c8_i147 < 30; c8_i147++) {
      c8_u[c8_i147 + c8_i145] = c8_b_inData[c8_i147 + c8_i145];
    }

    c8_i145 += 30;
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 2, 30, 30), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static const mxArray *c8_h_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_i148;
  int32_T c8_i149;
  int32_T c8_i150;
  real_T c8_b_inData[1860];
  int32_T c8_i151;
  int32_T c8_i152;
  int32_T c8_i153;
  real_T c8_u[1860];
  const mxArray *c8_y = NULL;
  SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc8_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_i148 = 0;
  for (c8_i149 = 0; c8_i149 < 30; c8_i149++) {
    for (c8_i150 = 0; c8_i150 < 62; c8_i150++) {
      c8_b_inData[c8_i150 + c8_i148] = (*(real_T (*)[1860])c8_inData)[c8_i150 +
        c8_i148];
    }

    c8_i148 += 62;
  }

  c8_i151 = 0;
  for (c8_i152 = 0; c8_i152 < 30; c8_i152++) {
    for (c8_i153 = 0; c8_i153 < 62; c8_i153++) {
      c8_u[c8_i153 + c8_i151] = c8_b_inData[c8_i153 + c8_i151];
    }

    c8_i151 += 62;
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 2, 62, 30), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static const mxArray *c8_i_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_i154;
  int32_T c8_i155;
  int32_T c8_i156;
  real_T c8_b_inData[60];
  int32_T c8_i157;
  int32_T c8_i158;
  int32_T c8_i159;
  real_T c8_u[60];
  const mxArray *c8_y = NULL;
  SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc8_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_i154 = 0;
  for (c8_i155 = 0; c8_i155 < 30; c8_i155++) {
    for (c8_i156 = 0; c8_i156 < 2; c8_i156++) {
      c8_b_inData[c8_i156 + c8_i154] = (*(real_T (*)[60])c8_inData)[c8_i156 +
        c8_i154];
    }

    c8_i154 += 2;
  }

  c8_i157 = 0;
  for (c8_i158 = 0; c8_i158 < 30; c8_i158++) {
    for (c8_i159 = 0; c8_i159 < 2; c8_i159++) {
      c8_u[c8_i159 + c8_i157] = c8_b_inData[c8_i159 + c8_i157];
    }

    c8_i157 += 2;
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 2, 2, 30), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static const mxArray *c8_j_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_i160;
  real_T c8_b_inData[30];
  int32_T c8_i161;
  real_T c8_u[30];
  const mxArray *c8_y = NULL;
  SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc8_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  for (c8_i160 = 0; c8_i160 < 30; c8_i160++) {
    c8_b_inData[c8_i160] = (*(real_T (*)[30])c8_inData)[c8_i160];
  }

  for (c8_i161 = 0; c8_i161 < 30; c8_i161++) {
    c8_u[c8_i161] = c8_b_inData[c8_i161];
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 2, 1, 30), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static void c8_g_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  real_T c8_y[30])
{
  real_T c8_dv10[30];
  int32_T c8_i162;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), c8_dv10, 1, 0, 0U, 1, 0U, 2, 1,
                30);
  for (c8_i162 = 0; c8_i162 < 30; c8_i162++) {
    c8_y[c8_i162] = c8_dv10[c8_i162];
  }

  sf_mex_destroy(&c8_u);
}

static void c8_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_LL_PP_ref;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y[30];
  int32_T c8_i163;
  SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc8_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c8_LL_PP_ref = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_LL_PP_ref), &c8_thisId,
                        c8_y);
  sf_mex_destroy(&c8_LL_PP_ref);
  for (c8_i163 = 0; c8_i163 < 30; c8_i163++) {
    (*(real_T (*)[30])c8_outData)[c8_i163] = c8_y[c8_i163];
  }

  sf_mex_destroy(&c8_mxArrayInData);
}

static void c8_h_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  real_T c8_y[8])
{
  real_T c8_dv11[8];
  int32_T c8_i164;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), c8_dv11, 1, 0, 0U, 1, 0U, 1, 8);
  for (c8_i164 = 0; c8_i164 < 8; c8_i164++) {
    c8_y[c8_i164] = c8_dv11[c8_i164];
  }

  sf_mex_destroy(&c8_u);
}

static void c8_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_betas;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y[8];
  int32_T c8_i165;
  SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc8_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c8_betas = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_betas), &c8_thisId, c8_y);
  sf_mex_destroy(&c8_betas);
  for (c8_i165 = 0; c8_i165 < 8; c8_i165++) {
    (*(real_T (*)[8])c8_outData)[c8_i165] = c8_y[c8_i165];
  }

  sf_mex_destroy(&c8_mxArrayInData);
}

static void c8_i_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  real_T c8_y[900])
{
  real_T c8_dv12[900];
  int32_T c8_i166;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), c8_dv12, 1, 0, 0U, 1, 0U, 2, 30,
                30);
  for (c8_i166 = 0; c8_i166 < 900; c8_i166++) {
    c8_y[c8_i166] = c8_dv12[c8_i166];
  }

  sf_mex_destroy(&c8_u);
}

static void c8_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_TT_PP;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y[900];
  int32_T c8_i167;
  int32_T c8_i168;
  int32_T c8_i169;
  SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc8_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c8_TT_PP = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_TT_PP), &c8_thisId, c8_y);
  sf_mex_destroy(&c8_TT_PP);
  c8_i167 = 0;
  for (c8_i168 = 0; c8_i168 < 30; c8_i168++) {
    for (c8_i169 = 0; c8_i169 < 30; c8_i169++) {
      (*(real_T (*)[900])c8_outData)[c8_i169 + c8_i167] = c8_y[c8_i169 + c8_i167];
    }

    c8_i167 += 30;
  }

  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_k_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  const mxArray *c8_y = NULL;
  SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc8_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

const mxArray *sf_c8_Hquad_control_LIB_MPC_get_eml_resolved_functions_info(void)
{
  const mxArray *c8_nameCaptureInfo;
  c8_ResolvedFunctionInfo c8_info[44];
  const mxArray *c8_m0 = NULL;
  int32_T c8_i170;
  c8_ResolvedFunctionInfo *c8_r0;
  c8_nameCaptureInfo = NULL;
  c8_nameCaptureInfo = NULL;
  c8_info_helper(c8_info);
  sf_mex_assign(&c8_m0, sf_mex_createstruct("nameCaptureInfo", 1, 44), FALSE);
  for (c8_i170 = 0; c8_i170 < 44; c8_i170++) {
    c8_r0 = &c8_info[c8_i170];
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c8_r0->context)), "context", "nameCaptureInfo",
                    c8_i170);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c8_r0->name)), "name", "nameCaptureInfo", c8_i170);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c8_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c8_i170);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c8_r0->resolved)), "resolved", "nameCaptureInfo",
                    c8_i170);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c8_i170);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c8_i170);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c8_i170);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c8_i170);
  }

  sf_mex_assign(&c8_nameCaptureInfo, c8_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c8_nameCaptureInfo);
  return c8_nameCaptureInfo;
}

static void c8_info_helper(c8_ResolvedFunctionInfo c8_info[44])
{
  c8_info[0].context = "";
  c8_info[0].name = "mtimes";
  c8_info[0].dominantType = "double";
  c8_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c8_info[0].fileTimeLo = 1289519692U;
  c8_info[0].fileTimeHi = 0U;
  c8_info[0].mFileTimeLo = 0U;
  c8_info[0].mFileTimeHi = 0U;
  c8_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c8_info[1].name = "eml_index_class";
  c8_info[1].dominantType = "";
  c8_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c8_info[1].fileTimeLo = 1323170578U;
  c8_info[1].fileTimeHi = 0U;
  c8_info[1].mFileTimeLo = 0U;
  c8_info[1].mFileTimeHi = 0U;
  c8_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c8_info[2].name = "eml_scalar_eg";
  c8_info[2].dominantType = "double";
  c8_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c8_info[2].fileTimeLo = 1286818796U;
  c8_info[2].fileTimeHi = 0U;
  c8_info[2].mFileTimeLo = 0U;
  c8_info[2].mFileTimeHi = 0U;
  c8_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c8_info[3].name = "eml_xgemm";
  c8_info[3].dominantType = "char";
  c8_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c8_info[3].fileTimeLo = 1299076772U;
  c8_info[3].fileTimeHi = 0U;
  c8_info[3].mFileTimeLo = 0U;
  c8_info[3].mFileTimeHi = 0U;
  c8_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c8_info[4].name = "eml_blas_inline";
  c8_info[4].dominantType = "";
  c8_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c8_info[4].fileTimeLo = 1299076768U;
  c8_info[4].fileTimeHi = 0U;
  c8_info[4].mFileTimeLo = 0U;
  c8_info[4].mFileTimeHi = 0U;
  c8_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c8_info[5].name = "mtimes";
  c8_info[5].dominantType = "double";
  c8_info[5].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c8_info[5].fileTimeLo = 1289519692U;
  c8_info[5].fileTimeHi = 0U;
  c8_info[5].mFileTimeLo = 0U;
  c8_info[5].mFileTimeHi = 0U;
  c8_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c8_info[6].name = "eml_index_class";
  c8_info[6].dominantType = "";
  c8_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c8_info[6].fileTimeLo = 1323170578U;
  c8_info[6].fileTimeHi = 0U;
  c8_info[6].mFileTimeLo = 0U;
  c8_info[6].mFileTimeHi = 0U;
  c8_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c8_info[7].name = "eml_scalar_eg";
  c8_info[7].dominantType = "double";
  c8_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c8_info[7].fileTimeLo = 1286818796U;
  c8_info[7].fileTimeHi = 0U;
  c8_info[7].mFileTimeLo = 0U;
  c8_info[7].mFileTimeHi = 0U;
  c8_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c8_info[8].name = "eml_refblas_xgemm";
  c8_info[8].dominantType = "char";
  c8_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c8_info[8].fileTimeLo = 1299076774U;
  c8_info[8].fileTimeHi = 0U;
  c8_info[8].mFileTimeLo = 0U;
  c8_info[8].mFileTimeHi = 0U;
  c8_info[9].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c8_info[9].name = "eml_xdotu";
  c8_info[9].dominantType = "double";
  c8_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c8_info[9].fileTimeLo = 1299076772U;
  c8_info[9].fileTimeHi = 0U;
  c8_info[9].mFileTimeLo = 0U;
  c8_info[9].mFileTimeHi = 0U;
  c8_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c8_info[10].name = "eml_blas_inline";
  c8_info[10].dominantType = "";
  c8_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c8_info[10].fileTimeLo = 1299076768U;
  c8_info[10].fileTimeHi = 0U;
  c8_info[10].mFileTimeLo = 0U;
  c8_info[10].mFileTimeHi = 0U;
  c8_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c8_info[11].name = "eml_xdot";
  c8_info[11].dominantType = "double";
  c8_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m";
  c8_info[11].fileTimeLo = 1299076772U;
  c8_info[11].fileTimeHi = 0U;
  c8_info[11].mFileTimeLo = 0U;
  c8_info[11].mFileTimeHi = 0U;
  c8_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m";
  c8_info[12].name = "eml_blas_inline";
  c8_info[12].dominantType = "";
  c8_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c8_info[12].fileTimeLo = 1299076768U;
  c8_info[12].fileTimeHi = 0U;
  c8_info[12].mFileTimeLo = 0U;
  c8_info[12].mFileTimeHi = 0U;
  c8_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m";
  c8_info[13].name = "eml_index_class";
  c8_info[13].dominantType = "";
  c8_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c8_info[13].fileTimeLo = 1323170578U;
  c8_info[13].fileTimeHi = 0U;
  c8_info[13].mFileTimeLo = 0U;
  c8_info[13].mFileTimeHi = 0U;
  c8_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m";
  c8_info[14].name = "eml_refblas_xdot";
  c8_info[14].dominantType = "double";
  c8_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c8_info[14].fileTimeLo = 1299076772U;
  c8_info[14].fileTimeHi = 0U;
  c8_info[14].mFileTimeLo = 0U;
  c8_info[14].mFileTimeHi = 0U;
  c8_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c8_info[15].name = "eml_refblas_xdotx";
  c8_info[15].dominantType = "char";
  c8_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c8_info[15].fileTimeLo = 1299076774U;
  c8_info[15].fileTimeHi = 0U;
  c8_info[15].mFileTimeLo = 0U;
  c8_info[15].mFileTimeHi = 0U;
  c8_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c8_info[16].name = "eml_scalar_eg";
  c8_info[16].dominantType = "double";
  c8_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c8_info[16].fileTimeLo = 1286818796U;
  c8_info[16].fileTimeHi = 0U;
  c8_info[16].mFileTimeLo = 0U;
  c8_info[16].mFileTimeHi = 0U;
  c8_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c8_info[17].name = "eml_index_class";
  c8_info[17].dominantType = "";
  c8_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c8_info[17].fileTimeLo = 1323170578U;
  c8_info[17].fileTimeHi = 0U;
  c8_info[17].mFileTimeLo = 0U;
  c8_info[17].mFileTimeHi = 0U;
  c8_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c8_info[18].name = "eml_index_minus";
  c8_info[18].dominantType = "double";
  c8_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c8_info[18].fileTimeLo = 1286818778U;
  c8_info[18].fileTimeHi = 0U;
  c8_info[18].mFileTimeLo = 0U;
  c8_info[18].mFileTimeHi = 0U;
  c8_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c8_info[19].name = "eml_index_class";
  c8_info[19].dominantType = "";
  c8_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c8_info[19].fileTimeLo = 1323170578U;
  c8_info[19].fileTimeHi = 0U;
  c8_info[19].mFileTimeLo = 0U;
  c8_info[19].mFileTimeHi = 0U;
  c8_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c8_info[20].name = "eml_index_times";
  c8_info[20].dominantType = "coder.internal.indexInt";
  c8_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c8_info[20].fileTimeLo = 1286818780U;
  c8_info[20].fileTimeHi = 0U;
  c8_info[20].mFileTimeLo = 0U;
  c8_info[20].mFileTimeHi = 0U;
  c8_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c8_info[21].name = "eml_index_class";
  c8_info[21].dominantType = "";
  c8_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c8_info[21].fileTimeLo = 1323170578U;
  c8_info[21].fileTimeHi = 0U;
  c8_info[21].mFileTimeLo = 0U;
  c8_info[21].mFileTimeHi = 0U;
  c8_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c8_info[22].name = "eml_index_plus";
  c8_info[22].dominantType = "coder.internal.indexInt";
  c8_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c8_info[22].fileTimeLo = 1286818778U;
  c8_info[22].fileTimeHi = 0U;
  c8_info[22].mFileTimeLo = 0U;
  c8_info[22].mFileTimeHi = 0U;
  c8_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c8_info[23].name = "eml_index_class";
  c8_info[23].dominantType = "";
  c8_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c8_info[23].fileTimeLo = 1323170578U;
  c8_info[23].fileTimeHi = 0U;
  c8_info[23].mFileTimeLo = 0U;
  c8_info[23].mFileTimeHi = 0U;
  c8_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c8_info[24].name = "eml_int_forloop_overflow_check";
  c8_info[24].dominantType = "";
  c8_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c8_info[24].fileTimeLo = 1346510340U;
  c8_info[24].fileTimeHi = 0U;
  c8_info[24].mFileTimeLo = 0U;
  c8_info[24].mFileTimeHi = 0U;
  c8_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c8_info[25].name = "intmax";
  c8_info[25].dominantType = "char";
  c8_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c8_info[25].fileTimeLo = 1311255316U;
  c8_info[25].fileTimeHi = 0U;
  c8_info[25].mFileTimeLo = 0U;
  c8_info[25].mFileTimeHi = 0U;
  c8_info[26].context = "";
  c8_info[26].name = "runFastGradient";
  c8_info[26].dominantType = "double";
  c8_info[26].resolved =
    "[E]/home/darivianos/Matlab/MPC_FastGradient/tools/runFastGradient.m";
  c8_info[26].fileTimeLo = 1331828792U;
  c8_info[26].fileTimeHi = 0U;
  c8_info[26].mFileTimeLo = 0U;
  c8_info[26].mFileTimeHi = 0U;
  c8_info[27].context =
    "[E]/home/darivianos/Matlab/MPC_FastGradient/tools/runFastGradient.m";
  c8_info[27].name = "mrdivide";
  c8_info[27].dominantType = "double";
  c8_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c8_info[27].fileTimeLo = 1357951548U;
  c8_info[27].fileTimeHi = 0U;
  c8_info[27].mFileTimeLo = 1319729966U;
  c8_info[27].mFileTimeHi = 0U;
  c8_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c8_info[28].name = "rdivide";
  c8_info[28].dominantType = "double";
  c8_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c8_info[28].fileTimeLo = 1346510388U;
  c8_info[28].fileTimeHi = 0U;
  c8_info[28].mFileTimeLo = 0U;
  c8_info[28].mFileTimeHi = 0U;
  c8_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c8_info[29].name = "eml_scalexp_compatible";
  c8_info[29].dominantType = "double";
  c8_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c8_info[29].fileTimeLo = 1286818796U;
  c8_info[29].fileTimeHi = 0U;
  c8_info[29].mFileTimeLo = 0U;
  c8_info[29].mFileTimeHi = 0U;
  c8_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c8_info[30].name = "eml_div";
  c8_info[30].dominantType = "double";
  c8_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c8_info[30].fileTimeLo = 1313347810U;
  c8_info[30].fileTimeHi = 0U;
  c8_info[30].mFileTimeLo = 0U;
  c8_info[30].mFileTimeHi = 0U;
  c8_info[31].context =
    "[E]/home/darivianos/Matlab/MPC_FastGradient/tools/runFastGradient.m";
  c8_info[31].name = "mtimes";
  c8_info[31].dominantType = "double";
  c8_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c8_info[31].fileTimeLo = 1289519692U;
  c8_info[31].fileTimeHi = 0U;
  c8_info[31].mFileTimeLo = 0U;
  c8_info[31].mFileTimeHi = 0U;
  c8_info[32].context =
    "[E]/home/darivianos/Matlab/MPC_FastGradient/tools/runFastGradient.m";
  c8_info[32].name = "min";
  c8_info[32].dominantType = "double";
  c8_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c8_info[32].fileTimeLo = 1311255318U;
  c8_info[32].fileTimeHi = 0U;
  c8_info[32].mFileTimeLo = 0U;
  c8_info[32].mFileTimeHi = 0U;
  c8_info[33].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c8_info[33].name = "eml_min_or_max";
  c8_info[33].dominantType = "char";
  c8_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c8_info[33].fileTimeLo = 1334071490U;
  c8_info[33].fileTimeHi = 0U;
  c8_info[33].mFileTimeLo = 0U;
  c8_info[33].mFileTimeHi = 0U;
  c8_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c8_info[34].name = "eml_scalar_eg";
  c8_info[34].dominantType = "double";
  c8_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c8_info[34].fileTimeLo = 1286818796U;
  c8_info[34].fileTimeHi = 0U;
  c8_info[34].mFileTimeLo = 0U;
  c8_info[34].mFileTimeHi = 0U;
  c8_info[35].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c8_info[35].name = "eml_scalexp_alloc";
  c8_info[35].dominantType = "double";
  c8_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c8_info[35].fileTimeLo = 1352424860U;
  c8_info[35].fileTimeHi = 0U;
  c8_info[35].mFileTimeLo = 0U;
  c8_info[35].mFileTimeHi = 0U;
  c8_info[36].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c8_info[36].name = "isequal";
  c8_info[36].dominantType = "double";
  c8_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c8_info[36].fileTimeLo = 1286818758U;
  c8_info[36].fileTimeHi = 0U;
  c8_info[36].mFileTimeLo = 0U;
  c8_info[36].mFileTimeHi = 0U;
  c8_info[37].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c8_info[37].name = "eml_isequal_core";
  c8_info[37].dominantType = "double";
  c8_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c8_info[37].fileTimeLo = 1286818786U;
  c8_info[37].fileTimeHi = 0U;
  c8_info[37].mFileTimeLo = 0U;
  c8_info[37].mFileTimeHi = 0U;
  c8_info[38].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m!isequal_scalar";
  c8_info[38].name = "isnan";
  c8_info[38].dominantType = "double";
  c8_info[38].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c8_info[38].fileTimeLo = 1286818760U;
  c8_info[38].fileTimeHi = 0U;
  c8_info[38].mFileTimeLo = 0U;
  c8_info[38].mFileTimeHi = 0U;
  c8_info[39].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c8_info[39].name = "eml_index_class";
  c8_info[39].dominantType = "";
  c8_info[39].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c8_info[39].fileTimeLo = 1323170578U;
  c8_info[39].fileTimeHi = 0U;
  c8_info[39].mFileTimeLo = 0U;
  c8_info[39].mFileTimeHi = 0U;
  c8_info[40].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c8_info[40].name = "eml_int_forloop_overflow_check";
  c8_info[40].dominantType = "";
  c8_info[40].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c8_info[40].fileTimeLo = 1346510340U;
  c8_info[40].fileTimeHi = 0U;
  c8_info[40].mFileTimeLo = 0U;
  c8_info[40].mFileTimeHi = 0U;
  c8_info[41].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  c8_info[41].name = "eml_scalar_eg";
  c8_info[41].dominantType = "double";
  c8_info[41].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c8_info[41].fileTimeLo = 1286818796U;
  c8_info[41].fileTimeHi = 0U;
  c8_info[41].mFileTimeLo = 0U;
  c8_info[41].mFileTimeHi = 0U;
  c8_info[42].context =
    "[E]/home/darivianos/Matlab/MPC_FastGradient/tools/runFastGradient.m";
  c8_info[42].name = "max";
  c8_info[42].dominantType = "double";
  c8_info[42].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/max.m";
  c8_info[42].fileTimeLo = 1311255316U;
  c8_info[42].fileTimeHi = 0U;
  c8_info[42].mFileTimeLo = 0U;
  c8_info[42].mFileTimeHi = 0U;
  c8_info[43].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/max.m";
  c8_info[43].name = "eml_min_or_max";
  c8_info[43].dominantType = "char";
  c8_info[43].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c8_info[43].fileTimeLo = 1334071490U;
  c8_info[43].fileTimeHi = 0U;
  c8_info[43].mFileTimeLo = 0U;
  c8_info[43].mFileTimeHi = 0U;
}

static void c8_eml_scalar_eg(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance)
{
}

static void c8_b_eml_scalar_eg(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance)
{
}

static void c8_c_eml_scalar_eg(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance)
{
}

static void c8_eml_xgemm(SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance,
  real_T c8_A[62], real_T c8_B[1860], real_T c8_C[30], real_T c8_b_C[30])
{
  int32_T c8_i171;
  int32_T c8_i172;
  real_T c8_b_A[62];
  int32_T c8_i173;
  real_T c8_b_B[1860];
  for (c8_i171 = 0; c8_i171 < 30; c8_i171++) {
    c8_b_C[c8_i171] = c8_C[c8_i171];
  }

  for (c8_i172 = 0; c8_i172 < 62; c8_i172++) {
    c8_b_A[c8_i172] = c8_A[c8_i172];
  }

  for (c8_i173 = 0; c8_i173 < 1860; c8_i173++) {
    c8_b_B[c8_i173] = c8_B[c8_i173];
  }

  c8_d_eml_xgemm(chartInstance, c8_b_A, c8_b_B, c8_b_C);
}

static void c8_d_eml_scalar_eg(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance)
{
}

static void c8_b_eml_xgemm(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, real_T c8_A[30], real_T c8_B[900], real_T c8_C[30], real_T
  c8_b_C[30])
{
  int32_T c8_i174;
  int32_T c8_i175;
  real_T c8_b_A[30];
  int32_T c8_i176;
  real_T c8_b_B[900];
  for (c8_i174 = 0; c8_i174 < 30; c8_i174++) {
    c8_b_C[c8_i174] = c8_C[c8_i174];
  }

  for (c8_i175 = 0; c8_i175 < 30; c8_i175++) {
    c8_b_A[c8_i175] = c8_A[c8_i175];
  }

  for (c8_i176 = 0; c8_i176 < 900; c8_i176++) {
    c8_b_B[c8_i176] = c8_B[c8_i176];
  }

  c8_e_eml_xgemm(chartInstance, c8_b_A, c8_b_B, c8_b_C);
}

static void c8_e_eml_scalar_eg(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance)
{
}

static void c8_f_eml_scalar_eg(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance)
{
}

static void c8_g_eml_scalar_eg(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance)
{
}

static void c8_c_eml_xgemm(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, real_T c8_A[900], real_T c8_B[30], real_T c8_C[30], real_T
  c8_b_C[30])
{
  int32_T c8_i177;
  int32_T c8_i178;
  real_T c8_b_A[900];
  int32_T c8_i179;
  real_T c8_b_B[30];
  for (c8_i177 = 0; c8_i177 < 30; c8_i177++) {
    c8_b_C[c8_i177] = c8_C[c8_i177];
  }

  for (c8_i178 = 0; c8_i178 < 900; c8_i178++) {
    c8_b_A[c8_i178] = c8_A[c8_i178];
  }

  for (c8_i179 = 0; c8_i179 < 30; c8_i179++) {
    c8_b_B[c8_i179] = c8_B[c8_i179];
  }

  c8_f_eml_xgemm(chartInstance, c8_b_A, c8_b_B, c8_b_C);
}

static void c8_h_eml_scalar_eg(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance)
{
}

static void c8_i_eml_scalar_eg(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance)
{
}

static void c8_j_eml_scalar_eg(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance)
{
}

static const mxArray *c8_l_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_u;
  const mxArray *c8_y = NULL;
  SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc8_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = *(int32_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static int32_T c8_j_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  int32_T c8_y;
  int32_T c8_i180;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_i180, 1, 6, 0U, 0, 0U, 0);
  c8_y = c8_i180;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_b_sfEvent;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  int32_T c8_y;
  SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc8_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c8_b_sfEvent = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_b_sfEvent),
    &c8_thisId);
  sf_mex_destroy(&c8_b_sfEvent);
  *(int32_T *)c8_outData = c8_y;
  sf_mex_destroy(&c8_mxArrayInData);
}

static uint8_T c8_k_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_b_is_active_c8_Hquad_control_LIB_MPC, const
  char_T *c8_identifier)
{
  uint8_T c8_y;
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_l_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c8_b_is_active_c8_Hquad_control_LIB_MPC), &c8_thisId);
  sf_mex_destroy(&c8_b_is_active_c8_Hquad_control_LIB_MPC);
  return c8_y;
}

static uint8_T c8_l_emlrt_marshallIn(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  uint8_T c8_y;
  uint8_T c8_u0;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_u0, 1, 3, 0U, 0, 0U, 0);
  c8_y = c8_u0;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_d_eml_xgemm(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, real_T c8_A[62], real_T c8_B[1860], real_T c8_C[30])
{
  real_T c8_alpha1;
  real_T c8_beta1;
  char_T c8_TRANSB;
  char_T c8_TRANSA;
  ptrdiff_t c8_m_t;
  ptrdiff_t c8_n_t;
  ptrdiff_t c8_k_t;
  ptrdiff_t c8_lda_t;
  ptrdiff_t c8_ldb_t;
  ptrdiff_t c8_ldc_t;
  double * c8_alpha1_t;
  double * c8_Aia0_t;
  double * c8_Bib0_t;
  double * c8_beta1_t;
  double * c8_Cic0_t;
  c8_alpha1 = 1.0;
  c8_beta1 = 0.0;
  c8_TRANSB = 'N';
  c8_TRANSA = 'N';
  c8_m_t = (ptrdiff_t)(1);
  c8_n_t = (ptrdiff_t)(30);
  c8_k_t = (ptrdiff_t)(62);
  c8_lda_t = (ptrdiff_t)(1);
  c8_ldb_t = (ptrdiff_t)(62);
  c8_ldc_t = (ptrdiff_t)(1);
  c8_alpha1_t = (double *)(&c8_alpha1);
  c8_Aia0_t = (double *)(&c8_A[0]);
  c8_Bib0_t = (double *)(&c8_B[0]);
  c8_beta1_t = (double *)(&c8_beta1);
  c8_Cic0_t = (double *)(&c8_C[0]);
  dgemm(&c8_TRANSA, &c8_TRANSB, &c8_m_t, &c8_n_t, &c8_k_t, c8_alpha1_t,
        c8_Aia0_t, &c8_lda_t, c8_Bib0_t, &c8_ldb_t, c8_beta1_t, c8_Cic0_t,
        &c8_ldc_t);
}

static void c8_e_eml_xgemm(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, real_T c8_A[30], real_T c8_B[900], real_T c8_C[30])
{
  real_T c8_alpha1;
  real_T c8_beta1;
  char_T c8_TRANSB;
  char_T c8_TRANSA;
  ptrdiff_t c8_m_t;
  ptrdiff_t c8_n_t;
  ptrdiff_t c8_k_t;
  ptrdiff_t c8_lda_t;
  ptrdiff_t c8_ldb_t;
  ptrdiff_t c8_ldc_t;
  double * c8_alpha1_t;
  double * c8_Aia0_t;
  double * c8_Bib0_t;
  double * c8_beta1_t;
  double * c8_Cic0_t;
  c8_alpha1 = 1.0;
  c8_beta1 = 0.0;
  c8_TRANSB = 'N';
  c8_TRANSA = 'N';
  c8_m_t = (ptrdiff_t)(1);
  c8_n_t = (ptrdiff_t)(30);
  c8_k_t = (ptrdiff_t)(30);
  c8_lda_t = (ptrdiff_t)(1);
  c8_ldb_t = (ptrdiff_t)(30);
  c8_ldc_t = (ptrdiff_t)(1);
  c8_alpha1_t = (double *)(&c8_alpha1);
  c8_Aia0_t = (double *)(&c8_A[0]);
  c8_Bib0_t = (double *)(&c8_B[0]);
  c8_beta1_t = (double *)(&c8_beta1);
  c8_Cic0_t = (double *)(&c8_C[0]);
  dgemm(&c8_TRANSA, &c8_TRANSB, &c8_m_t, &c8_n_t, &c8_k_t, c8_alpha1_t,
        c8_Aia0_t, &c8_lda_t, c8_Bib0_t, &c8_ldb_t, c8_beta1_t, c8_Cic0_t,
        &c8_ldc_t);
}

static void c8_f_eml_xgemm(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, real_T c8_A[900], real_T c8_B[30], real_T c8_C[30])
{
  real_T c8_alpha1;
  real_T c8_beta1;
  char_T c8_TRANSB;
  char_T c8_TRANSA;
  ptrdiff_t c8_m_t;
  ptrdiff_t c8_n_t;
  ptrdiff_t c8_k_t;
  ptrdiff_t c8_lda_t;
  ptrdiff_t c8_ldb_t;
  ptrdiff_t c8_ldc_t;
  double * c8_alpha1_t;
  double * c8_Aia0_t;
  double * c8_Bib0_t;
  double * c8_beta1_t;
  double * c8_Cic0_t;
  c8_alpha1 = 1.0;
  c8_beta1 = 0.0;
  c8_TRANSB = 'N';
  c8_TRANSA = 'N';
  c8_m_t = (ptrdiff_t)(30);
  c8_n_t = (ptrdiff_t)(1);
  c8_k_t = (ptrdiff_t)(30);
  c8_lda_t = (ptrdiff_t)(30);
  c8_ldb_t = (ptrdiff_t)(30);
  c8_ldc_t = (ptrdiff_t)(30);
  c8_alpha1_t = (double *)(&c8_alpha1);
  c8_Aia0_t = (double *)(&c8_A[0]);
  c8_Bib0_t = (double *)(&c8_B[0]);
  c8_beta1_t = (double *)(&c8_beta1);
  c8_Cic0_t = (double *)(&c8_C[0]);
  dgemm(&c8_TRANSA, &c8_TRANSB, &c8_m_t, &c8_n_t, &c8_k_t, c8_alpha1_t,
        c8_Aia0_t, &c8_lda_t, c8_Bib0_t, &c8_ldb_t, c8_beta1_t, c8_Cic0_t,
        &c8_ldc_t);
}

static void init_dsm_address_info(SFc8_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c8_Hquad_control_LIB_MPC_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(500497163U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2073238302U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2144690521U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2190295639U);
}

mxArray *sf_c8_Hquad_control_LIB_MPC_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("p9NXNLYRd7QjiiMwQAefsC");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,16,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(30);
      pr[1] = (double)(30);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(30);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(62);
      pr[1] = (double)(30);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(30);
      pr[1] = (double)(30);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(2);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(30);
      pr[1] = (double)(30);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(2);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(2);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(62);
      pr[1] = (double)(1);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(30);
      pr[1] = (double)(1);
      mxSetField(mxData,10,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,10,"type",mxType);
    }

    mxSetField(mxData,10,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,11,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,11,"type",mxType);
    }

    mxSetField(mxData,11,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(8);
      pr[1] = (double)(1);
      mxSetField(mxData,12,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,12,"type",mxType);
    }

    mxSetField(mxData,12,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,13,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,13,"type",mxType);
    }

    mxSetField(mxData,13,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,14,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,14,"type",mxType);
    }

    mxSetField(mxData,14,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(30);
      pr[1] = (double)(1);
      mxSetField(mxData,15,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,15,"type",mxType);
    }

    mxSetField(mxData,15,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(30);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c8_Hquad_control_LIB_MPC_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c8_Hquad_control_LIB_MPC(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[16],T\"J_star\",},{M[1],M[21],T\"V_init_out\",},{M[1],M[20],T\"u_buff_out\",},{M[1],M[5],T\"u_opt\",},{M[8],M[0],T\"is_active_c8_Hquad_control_LIB_MPC\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c8_Hquad_control_LIB_MPC_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
    chartInstance = (SFc8_Hquad_control_LIB_MPCInstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _Hquad_control_LIB_MPCMachineNumber_,
           8,
           1,
           1,
           20,
           0,
           0,
           0,
           0,
           1,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_Hquad_control_LIB_MPCMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_Hquad_control_LIB_MPCMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _Hquad_control_LIB_MPCMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"TT_PP");
          _SFD_SET_DATA_PROPS(1,2,0,1,"u_opt");
          _SFD_SET_DATA_PROPS(2,1,1,0,"LL_PP");
          _SFD_SET_DATA_PROPS(3,1,1,0,"LL_ref_PP");
          _SFD_SET_DATA_PROPS(4,1,1,0,"LL_U_ref_PP");
          _SFD_SET_DATA_PROPS(5,2,0,1,"J_star");
          _SFD_SET_DATA_PROPS(6,2,0,1,"u_buff_out");
          _SFD_SET_DATA_PROPS(7,2,0,1,"V_init_out");
          _SFD_SET_DATA_PROPS(8,1,1,0,"MM");
          _SFD_SET_DATA_PROPS(9,1,1,0,"PP");
          _SFD_SET_DATA_PROPS(10,1,1,0,"AA_delay");
          _SFD_SET_DATA_PROPS(11,1,1,0,"BB_delay");
          _SFD_SET_DATA_PROPS(12,1,1,0,"x");
          _SFD_SET_DATA_PROPS(13,1,1,0,"X_ref");
          _SFD_SET_DATA_PROPS(14,1,1,0,"V_max");
          _SFD_SET_DATA_PROPS(15,1,1,0,"i_min");
          _SFD_SET_DATA_PROPS(16,1,1,0,"betas");
          _SFD_SET_DATA_PROPS(17,1,1,0,"L");
          _SFD_SET_DATA_PROPS(18,1,1,0,"u_buff");
          _SFD_SET_DATA_PROPS(19,1,1,0,"V_init");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,2,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1440);
        _SFD_CV_INIT_EML_IF(0,1,0,478,496,524,584);
        _SFD_CV_INIT_EML_IF(0,1,1,1230,1248,1275,1348);
        _SFD_CV_INIT_SCRIPT(0,1,6,0,0,0,1,0,2,2);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"runFastGradient",0,-1,2478);
        _SFD_CV_INIT_SCRIPT_IF(0,0,1281,1297,-1,1318);
        _SFD_CV_INIT_SCRIPT_IF(0,1,1487,1497,-1,1725);
        _SFD_CV_INIT_SCRIPT_IF(0,2,1560,1594,-1,1721);
        _SFD_CV_INIT_SCRIPT_IF(0,3,2052,2062,-1,2285);
        _SFD_CV_INIT_SCRIPT_IF(0,4,2133,2167,-1,2277);
        _SFD_CV_INIT_SCRIPT_IF(0,5,2368,2379,-1,2413);
        _SFD_CV_INIT_SCRIPT_FOR(0,0,1763,1777,2289);

        {
          static int condStart[] = { 1285 };

          static int condEnd[] = { 1297 };

          static int pfixExpr[] = { 0, -1 };

          _SFD_CV_INIT_SCRIPT_MCDC(0,0,1284,1297,1,0,&(condStart[0]),&(condEnd[0]),
            2,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 2372 };

          static int condEnd[] = { 2379 };

          static int pfixExpr[] = { 0, -1 };

          _SFD_CV_INIT_SCRIPT_MCDC(0,1,2371,2379,1,1,&(condStart[0]),&(condEnd[0]),
            2,&(pfixExpr[0]));
        }

        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 30;
          dimVector[1]= 30;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_g_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c8_c_sf_marshallOut,(MexInFcnForType)c8_c_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 30;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_i_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 62;
          dimVector[1]= 30;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_h_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 30;
          dimVector[1]= 30;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_g_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c8_c_sf_marshallOut,(MexInFcnForType)c8_c_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_b_sf_marshallOut,(MexInFcnForType)
            c8_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 30;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)
            c8_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 30;
          dimVector[1]= 30;
          _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_g_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 62;
          _SFD_SET_DATA_COMPILED_PROPS(13,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 30;
          _SFD_SET_DATA_COMPILED_PROPS(14,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(15,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c8_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 8;
          _SFD_SET_DATA_COMPILED_PROPS(16,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(17,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c8_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(18,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 30;
          _SFD_SET_DATA_COMPILED_PROPS(19,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T *c8_u_opt;
          real_T *c8_J_star;
          real_T *c8_i_min;
          real_T *c8_L;
          real_T (*c8_TT_PP)[900];
          real_T (*c8_LL_PP)[60];
          real_T (*c8_LL_ref_PP)[1860];
          real_T (*c8_LL_U_ref_PP)[900];
          real_T (*c8_u_buff_out)[2];
          real_T (*c8_V_init_out)[30];
          real_T (*c8_MM)[4];
          real_T (*c8_PP)[900];
          real_T (*c8_AA_delay)[4];
          real_T (*c8_BB_delay)[4];
          real_T (*c8_x)[2];
          real_T (*c8_X_ref)[62];
          real_T (*c8_V_max)[30];
          real_T (*c8_betas)[8];
          real_T (*c8_u_buff)[2];
          real_T (*c8_V_init)[30];
          c8_V_init = (real_T (*)[30])ssGetInputPortSignal(chartInstance->S, 15);
          c8_u_buff = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 14);
          c8_L = (real_T *)ssGetInputPortSignal(chartInstance->S, 13);
          c8_betas = (real_T (*)[8])ssGetInputPortSignal(chartInstance->S, 12);
          c8_i_min = (real_T *)ssGetInputPortSignal(chartInstance->S, 11);
          c8_V_max = (real_T (*)[30])ssGetInputPortSignal(chartInstance->S, 10);
          c8_X_ref = (real_T (*)[62])ssGetInputPortSignal(chartInstance->S, 9);
          c8_x = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 8);
          c8_BB_delay = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 7);
          c8_AA_delay = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 6);
          c8_PP = (real_T (*)[900])ssGetInputPortSignal(chartInstance->S, 5);
          c8_MM = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 4);
          c8_V_init_out = (real_T (*)[30])ssGetOutputPortSignal(chartInstance->S,
            4);
          c8_u_buff_out = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S,
            3);
          c8_J_star = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c8_LL_U_ref_PP = (real_T (*)[900])ssGetInputPortSignal
            (chartInstance->S, 3);
          c8_LL_ref_PP = (real_T (*)[1860])ssGetInputPortSignal(chartInstance->S,
            2);
          c8_LL_PP = (real_T (*)[60])ssGetInputPortSignal(chartInstance->S, 1);
          c8_u_opt = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c8_TT_PP = (real_T (*)[900])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c8_TT_PP);
          _SFD_SET_DATA_VALUE_PTR(1U, c8_u_opt);
          _SFD_SET_DATA_VALUE_PTR(2U, *c8_LL_PP);
          _SFD_SET_DATA_VALUE_PTR(3U, *c8_LL_ref_PP);
          _SFD_SET_DATA_VALUE_PTR(4U, *c8_LL_U_ref_PP);
          _SFD_SET_DATA_VALUE_PTR(5U, c8_J_star);
          _SFD_SET_DATA_VALUE_PTR(6U, *c8_u_buff_out);
          _SFD_SET_DATA_VALUE_PTR(7U, *c8_V_init_out);
          _SFD_SET_DATA_VALUE_PTR(8U, *c8_MM);
          _SFD_SET_DATA_VALUE_PTR(9U, *c8_PP);
          _SFD_SET_DATA_VALUE_PTR(10U, *c8_AA_delay);
          _SFD_SET_DATA_VALUE_PTR(11U, *c8_BB_delay);
          _SFD_SET_DATA_VALUE_PTR(12U, *c8_x);
          _SFD_SET_DATA_VALUE_PTR(13U, *c8_X_ref);
          _SFD_SET_DATA_VALUE_PTR(14U, *c8_V_max);
          _SFD_SET_DATA_VALUE_PTR(15U, c8_i_min);
          _SFD_SET_DATA_VALUE_PTR(16U, *c8_betas);
          _SFD_SET_DATA_VALUE_PTR(17U, c8_L);
          _SFD_SET_DATA_VALUE_PTR(18U, *c8_u_buff);
          _SFD_SET_DATA_VALUE_PTR(19U, *c8_V_init);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _Hquad_control_LIB_MPCMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "z1TIkCO6Q4kMPs8uruIiAH";
}

static void sf_opaque_initialize_c8_Hquad_control_LIB_MPC(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc8_Hquad_control_LIB_MPCInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c8_Hquad_control_LIB_MPC
    ((SFc8_Hquad_control_LIB_MPCInstanceStruct*) chartInstanceVar);
  initialize_c8_Hquad_control_LIB_MPC((SFc8_Hquad_control_LIB_MPCInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c8_Hquad_control_LIB_MPC(void *chartInstanceVar)
{
  enable_c8_Hquad_control_LIB_MPC((SFc8_Hquad_control_LIB_MPCInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c8_Hquad_control_LIB_MPC(void *chartInstanceVar)
{
  disable_c8_Hquad_control_LIB_MPC((SFc8_Hquad_control_LIB_MPCInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c8_Hquad_control_LIB_MPC(void *chartInstanceVar)
{
  sf_c8_Hquad_control_LIB_MPC((SFc8_Hquad_control_LIB_MPCInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c8_Hquad_control_LIB_MPC
  (SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c8_Hquad_control_LIB_MPC
    ((SFc8_Hquad_control_LIB_MPCInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c8_Hquad_control_LIB_MPC();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c8_Hquad_control_LIB_MPC(SimStruct* S,
  const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c8_Hquad_control_LIB_MPC();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c8_Hquad_control_LIB_MPC
    ((SFc8_Hquad_control_LIB_MPCInstanceStruct*)chartInfo->chartInstance,
     mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c8_Hquad_control_LIB_MPC(SimStruct*
  S)
{
  return sf_internal_get_sim_state_c8_Hquad_control_LIB_MPC(S);
}

static void sf_opaque_set_sim_state_c8_Hquad_control_LIB_MPC(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c8_Hquad_control_LIB_MPC(S, st);
}

static void sf_opaque_terminate_c8_Hquad_control_LIB_MPC(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc8_Hquad_control_LIB_MPCInstanceStruct*) chartInstanceVar)
      ->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Hquad_control_LIB_MPC_optimization_info();
    }

    finalize_c8_Hquad_control_LIB_MPC((SFc8_Hquad_control_LIB_MPCInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc8_Hquad_control_LIB_MPC
    ((SFc8_Hquad_control_LIB_MPCInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c8_Hquad_control_LIB_MPC(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c8_Hquad_control_LIB_MPC
      ((SFc8_Hquad_control_LIB_MPCInstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c8_Hquad_control_LIB_MPC(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_Hquad_control_LIB_MPC_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      8);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,8,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,8,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,8);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 8, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 9, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 10, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 11, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 12, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 13, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 14, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 15, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,8,16);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,8,4);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=4; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 16; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,8);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1299639661U));
  ssSetChecksum1(S,(2016177138U));
  ssSetChecksum2(S,(62668147U));
  ssSetChecksum3(S,(3280862160U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c8_Hquad_control_LIB_MPC(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c8_Hquad_control_LIB_MPC(SimStruct *S)
{
  SFc8_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc8_Hquad_control_LIB_MPCInstanceStruct *)utMalloc(sizeof
    (SFc8_Hquad_control_LIB_MPCInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc8_Hquad_control_LIB_MPCInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c8_Hquad_control_LIB_MPC;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c8_Hquad_control_LIB_MPC;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c8_Hquad_control_LIB_MPC;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c8_Hquad_control_LIB_MPC;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c8_Hquad_control_LIB_MPC;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c8_Hquad_control_LIB_MPC;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c8_Hquad_control_LIB_MPC;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c8_Hquad_control_LIB_MPC;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c8_Hquad_control_LIB_MPC;
  chartInstance->chartInfo.mdlStart = mdlStart_c8_Hquad_control_LIB_MPC;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c8_Hquad_control_LIB_MPC;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c8_Hquad_control_LIB_MPC_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c8_Hquad_control_LIB_MPC(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c8_Hquad_control_LIB_MPC(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c8_Hquad_control_LIB_MPC(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c8_Hquad_control_LIB_MPC_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
