/* Include files */

#include <stddef.h>
#include "blas.h"
#include "Hquad_control_LIB_MPC_sfun.h"
#include "c20_Hquad_control_LIB_MPC.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "Hquad_control_LIB_MPC_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c20_debug_family_names[7] = { "pred_horizon", "X_ref_temp",
  "nargin", "nargout", "x_ref", "x_dot_ref", "X_ref" };

/* Function Declarations */
static void initialize_c20_Hquad_control_LIB_MPC
  (SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance);
static void initialize_params_c20_Hquad_control_LIB_MPC
  (SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance);
static void enable_c20_Hquad_control_LIB_MPC
  (SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance);
static void disable_c20_Hquad_control_LIB_MPC
  (SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance);
static void c20_update_debugger_state_c20_Hquad_control_LIB_MPC
  (SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c20_Hquad_control_LIB_MPC
  (SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance);
static void set_sim_state_c20_Hquad_control_LIB_MPC
  (SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance, const mxArray
   *c20_st);
static void finalize_c20_Hquad_control_LIB_MPC
  (SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance);
static void sf_c20_Hquad_control_LIB_MPC
  (SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance);
static void initSimStructsc20_Hquad_control_LIB_MPC
  (SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance);
static void registerMessagesc20_Hquad_control_LIB_MPC
  (SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c20_machineNumber, uint32_T
  c20_chartNumber);
static const mxArray *c20_sf_marshallOut(void *chartInstanceVoid, void
  *c20_inData);
static void c20_emlrt_marshallIn(SFc20_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c20_X_ref, const char_T *c20_identifier, real_T
  c20_y[62]);
static void c20_b_emlrt_marshallIn(SFc20_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c20_u, const emlrtMsgIdentifier *c20_parentId,
  real_T c20_y[62]);
static void c20_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c20_mxArrayInData, const char_T *c20_varName, void *c20_outData);
static const mxArray *c20_b_sf_marshallOut(void *chartInstanceVoid, void
  *c20_inData);
static real_T c20_c_emlrt_marshallIn(SFc20_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c20_u, const emlrtMsgIdentifier *c20_parentId);
static void c20_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c20_mxArrayInData, const char_T *c20_varName, void *c20_outData);
static const mxArray *c20_c_sf_marshallOut(void *chartInstanceVoid, void
  *c20_inData);
static void c20_d_emlrt_marshallIn(SFc20_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c20_u, const emlrtMsgIdentifier *c20_parentId,
  real_T c20_y[62]);
static void c20_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c20_mxArrayInData, const char_T *c20_varName, void *c20_outData);
static void c20_info_helper(c20_ResolvedFunctionInfo c20_info[22]);
static const mxArray *c20_d_sf_marshallOut(void *chartInstanceVoid, void
  *c20_inData);
static int32_T c20_e_emlrt_marshallIn(SFc20_Hquad_control_LIB_MPCInstanceStruct *
  chartInstance, const mxArray *c20_u, const emlrtMsgIdentifier *c20_parentId);
static void c20_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c20_mxArrayInData, const char_T *c20_varName, void *c20_outData);
static uint8_T c20_f_emlrt_marshallIn(SFc20_Hquad_control_LIB_MPCInstanceStruct *
  chartInstance, const mxArray *c20_b_is_active_c20_Hquad_control_LIB_MPC, const
  char_T *c20_identifier);
static uint8_T c20_g_emlrt_marshallIn(SFc20_Hquad_control_LIB_MPCInstanceStruct *
  chartInstance, const mxArray *c20_u, const emlrtMsgIdentifier *c20_parentId);
static void init_dsm_address_info(SFc20_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c20_Hquad_control_LIB_MPC
  (SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance)
{
  chartInstance->c20_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c20_is_active_c20_Hquad_control_LIB_MPC = 0U;
}

static void initialize_params_c20_Hquad_control_LIB_MPC
  (SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance)
{
}

static void enable_c20_Hquad_control_LIB_MPC
  (SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c20_Hquad_control_LIB_MPC
  (SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c20_update_debugger_state_c20_Hquad_control_LIB_MPC
  (SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c20_Hquad_control_LIB_MPC
  (SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance)
{
  const mxArray *c20_st;
  const mxArray *c20_y = NULL;
  int32_T c20_i0;
  real_T c20_u[62];
  const mxArray *c20_b_y = NULL;
  uint8_T c20_hoistedGlobal;
  uint8_T c20_b_u;
  const mxArray *c20_c_y = NULL;
  real_T (*c20_X_ref)[62];
  c20_X_ref = (real_T (*)[62])ssGetOutputPortSignal(chartInstance->S, 1);
  c20_st = NULL;
  c20_st = NULL;
  c20_y = NULL;
  sf_mex_assign(&c20_y, sf_mex_createcellarray(2), FALSE);
  for (c20_i0 = 0; c20_i0 < 62; c20_i0++) {
    c20_u[c20_i0] = (*c20_X_ref)[c20_i0];
  }

  c20_b_y = NULL;
  sf_mex_assign(&c20_b_y, sf_mex_create("y", c20_u, 0, 0U, 1U, 0U, 1, 62), FALSE);
  sf_mex_setcell(c20_y, 0, c20_b_y);
  c20_hoistedGlobal = chartInstance->c20_is_active_c20_Hquad_control_LIB_MPC;
  c20_b_u = c20_hoistedGlobal;
  c20_c_y = NULL;
  sf_mex_assign(&c20_c_y, sf_mex_create("y", &c20_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c20_y, 1, c20_c_y);
  sf_mex_assign(&c20_st, c20_y, FALSE);
  return c20_st;
}

static void set_sim_state_c20_Hquad_control_LIB_MPC
  (SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance, const mxArray
   *c20_st)
{
  const mxArray *c20_u;
  real_T c20_dv0[62];
  int32_T c20_i1;
  real_T (*c20_X_ref)[62];
  c20_X_ref = (real_T (*)[62])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c20_doneDoubleBufferReInit = TRUE;
  c20_u = sf_mex_dup(c20_st);
  c20_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c20_u, 0)),
                       "X_ref", c20_dv0);
  for (c20_i1 = 0; c20_i1 < 62; c20_i1++) {
    (*c20_X_ref)[c20_i1] = c20_dv0[c20_i1];
  }

  chartInstance->c20_is_active_c20_Hquad_control_LIB_MPC =
    c20_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c20_u, 1)),
    "is_active_c20_Hquad_control_LIB_MPC");
  sf_mex_destroy(&c20_u);
  c20_update_debugger_state_c20_Hquad_control_LIB_MPC(chartInstance);
  sf_mex_destroy(&c20_st);
}

static void finalize_c20_Hquad_control_LIB_MPC
  (SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance)
{
}

static void sf_c20_Hquad_control_LIB_MPC
  (SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance)
{
  int32_T c20_i2;
  real_T c20_hoistedGlobal;
  real_T c20_b_hoistedGlobal;
  real_T c20_x_ref;
  real_T c20_x_dot_ref;
  uint32_T c20_debug_family_var_map[7];
  real_T c20_pred_horizon;
  real_T c20_X_ref_temp[62];
  real_T c20_nargin = 2.0;
  real_T c20_nargout = 1.0;
  real_T c20_X_ref[62];
  real_T c20_a;
  int32_T c20_i3;
  real_T c20_y[31];
  real_T c20_b_a;
  int32_T c20_i4;
  real_T c20_b_y[31];
  int32_T c20_i5;
  int32_T c20_i6;
  int32_T c20_i7;
  int32_T c20_i8;
  int32_T c20_i9;
  real_T c20_x[62];
  int32_T c20_k;
  int32_T c20_b_k;
  real_T c20_c_y[62];
  int32_T c20_i10;
  int32_T c20_i11;
  real_T *c20_b_x_ref;
  real_T *c20_b_x_dot_ref;
  real_T (*c20_b_X_ref)[62];
  c20_b_X_ref = (real_T (*)[62])ssGetOutputPortSignal(chartInstance->S, 1);
  c20_b_x_dot_ref = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c20_b_x_ref = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 12U, chartInstance->c20_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c20_b_x_ref, 0U);
  _SFD_DATA_RANGE_CHECK(*c20_b_x_dot_ref, 1U);
  for (c20_i2 = 0; c20_i2 < 62; c20_i2++) {
    _SFD_DATA_RANGE_CHECK((*c20_b_X_ref)[c20_i2], 2U);
  }

  chartInstance->c20_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 12U, chartInstance->c20_sfEvent);
  c20_hoistedGlobal = *c20_b_x_ref;
  c20_b_hoistedGlobal = *c20_b_x_dot_ref;
  c20_x_ref = c20_hoistedGlobal;
  c20_x_dot_ref = c20_b_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 7U, 7U, c20_debug_family_names,
    c20_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c20_pred_horizon, 0U, c20_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c20_X_ref_temp, 1U, c20_c_sf_marshallOut,
    c20_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c20_nargin, 2U, c20_b_sf_marshallOut,
    c20_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c20_nargout, 3U, c20_b_sf_marshallOut,
    c20_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c20_x_ref, 4U, c20_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c20_x_dot_ref, 5U, c20_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c20_X_ref, 6U, c20_sf_marshallOut,
    c20_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c20_sfEvent, 3);
  c20_pred_horizon = 30.0;
  _SFD_EML_CALL(0U, chartInstance->c20_sfEvent, 5);
  c20_a = c20_x_ref;
  for (c20_i3 = 0; c20_i3 < 31; c20_i3++) {
    c20_y[c20_i3] = c20_a;
  }

  c20_b_a = c20_x_dot_ref;
  for (c20_i4 = 0; c20_i4 < 31; c20_i4++) {
    c20_b_y[c20_i4] = c20_b_a;
  }

  c20_i5 = 0;
  for (c20_i6 = 0; c20_i6 < 31; c20_i6++) {
    c20_X_ref_temp[c20_i5] = c20_y[c20_i6];
    c20_i5 += 2;
  }

  c20_i7 = 0;
  for (c20_i8 = 0; c20_i8 < 31; c20_i8++) {
    c20_X_ref_temp[c20_i7 + 1] = c20_b_y[c20_i8];
    c20_i7 += 2;
  }

  _SFD_EML_CALL(0U, chartInstance->c20_sfEvent, 7);
  for (c20_i9 = 0; c20_i9 < 62; c20_i9++) {
    c20_x[c20_i9] = c20_X_ref_temp[c20_i9];
  }

  for (c20_k = 1; c20_k < 63; c20_k++) {
    c20_b_k = c20_k;
    c20_c_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c20_b_k), 1, 62, 1, 0) - 1] = c20_x[_SFD_EML_ARRAY_BOUNDS_CHECK("",
      (int32_T)_SFD_INTEGER_CHECK("", (real_T)c20_b_k), 1, 62, 1, 0) - 1];
  }

  for (c20_i10 = 0; c20_i10 < 62; c20_i10++) {
    c20_X_ref[c20_i10] = c20_c_y[c20_i10];
  }

  _SFD_EML_CALL(0U, chartInstance->c20_sfEvent, -7);
  _SFD_SYMBOL_SCOPE_POP();
  for (c20_i11 = 0; c20_i11 < 62; c20_i11++) {
    (*c20_b_X_ref)[c20_i11] = c20_X_ref[c20_i11];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c20_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_Hquad_control_LIB_MPCMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc20_Hquad_control_LIB_MPC
  (SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance)
{
}

static void registerMessagesc20_Hquad_control_LIB_MPC
  (SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c20_machineNumber, uint32_T
  c20_chartNumber)
{
}

static const mxArray *c20_sf_marshallOut(void *chartInstanceVoid, void
  *c20_inData)
{
  const mxArray *c20_mxArrayOutData = NULL;
  int32_T c20_i12;
  real_T c20_b_inData[62];
  int32_T c20_i13;
  real_T c20_u[62];
  const mxArray *c20_y = NULL;
  SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc20_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c20_mxArrayOutData = NULL;
  for (c20_i12 = 0; c20_i12 < 62; c20_i12++) {
    c20_b_inData[c20_i12] = (*(real_T (*)[62])c20_inData)[c20_i12];
  }

  for (c20_i13 = 0; c20_i13 < 62; c20_i13++) {
    c20_u[c20_i13] = c20_b_inData[c20_i13];
  }

  c20_y = NULL;
  sf_mex_assign(&c20_y, sf_mex_create("y", c20_u, 0, 0U, 1U, 0U, 1, 62), FALSE);
  sf_mex_assign(&c20_mxArrayOutData, c20_y, FALSE);
  return c20_mxArrayOutData;
}

static void c20_emlrt_marshallIn(SFc20_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c20_X_ref, const char_T *c20_identifier, real_T
  c20_y[62])
{
  emlrtMsgIdentifier c20_thisId;
  c20_thisId.fIdentifier = c20_identifier;
  c20_thisId.fParent = NULL;
  c20_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c20_X_ref), &c20_thisId,
    c20_y);
  sf_mex_destroy(&c20_X_ref);
}

static void c20_b_emlrt_marshallIn(SFc20_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c20_u, const emlrtMsgIdentifier *c20_parentId,
  real_T c20_y[62])
{
  real_T c20_dv1[62];
  int32_T c20_i14;
  sf_mex_import(c20_parentId, sf_mex_dup(c20_u), c20_dv1, 1, 0, 0U, 1, 0U, 1, 62);
  for (c20_i14 = 0; c20_i14 < 62; c20_i14++) {
    c20_y[c20_i14] = c20_dv1[c20_i14];
  }

  sf_mex_destroy(&c20_u);
}

static void c20_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c20_mxArrayInData, const char_T *c20_varName, void *c20_outData)
{
  const mxArray *c20_X_ref;
  const char_T *c20_identifier;
  emlrtMsgIdentifier c20_thisId;
  real_T c20_y[62];
  int32_T c20_i15;
  SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc20_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c20_X_ref = sf_mex_dup(c20_mxArrayInData);
  c20_identifier = c20_varName;
  c20_thisId.fIdentifier = c20_identifier;
  c20_thisId.fParent = NULL;
  c20_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c20_X_ref), &c20_thisId,
    c20_y);
  sf_mex_destroy(&c20_X_ref);
  for (c20_i15 = 0; c20_i15 < 62; c20_i15++) {
    (*(real_T (*)[62])c20_outData)[c20_i15] = c20_y[c20_i15];
  }

  sf_mex_destroy(&c20_mxArrayInData);
}

static const mxArray *c20_b_sf_marshallOut(void *chartInstanceVoid, void
  *c20_inData)
{
  const mxArray *c20_mxArrayOutData = NULL;
  real_T c20_u;
  const mxArray *c20_y = NULL;
  SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc20_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c20_mxArrayOutData = NULL;
  c20_u = *(real_T *)c20_inData;
  c20_y = NULL;
  sf_mex_assign(&c20_y, sf_mex_create("y", &c20_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c20_mxArrayOutData, c20_y, FALSE);
  return c20_mxArrayOutData;
}

static real_T c20_c_emlrt_marshallIn(SFc20_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c20_u, const emlrtMsgIdentifier *c20_parentId)
{
  real_T c20_y;
  real_T c20_d0;
  sf_mex_import(c20_parentId, sf_mex_dup(c20_u), &c20_d0, 1, 0, 0U, 0, 0U, 0);
  c20_y = c20_d0;
  sf_mex_destroy(&c20_u);
  return c20_y;
}

static void c20_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c20_mxArrayInData, const char_T *c20_varName, void *c20_outData)
{
  const mxArray *c20_nargout;
  const char_T *c20_identifier;
  emlrtMsgIdentifier c20_thisId;
  real_T c20_y;
  SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc20_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c20_nargout = sf_mex_dup(c20_mxArrayInData);
  c20_identifier = c20_varName;
  c20_thisId.fIdentifier = c20_identifier;
  c20_thisId.fParent = NULL;
  c20_y = c20_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c20_nargout),
    &c20_thisId);
  sf_mex_destroy(&c20_nargout);
  *(real_T *)c20_outData = c20_y;
  sf_mex_destroy(&c20_mxArrayInData);
}

static const mxArray *c20_c_sf_marshallOut(void *chartInstanceVoid, void
  *c20_inData)
{
  const mxArray *c20_mxArrayOutData = NULL;
  int32_T c20_i16;
  int32_T c20_i17;
  int32_T c20_i18;
  real_T c20_b_inData[62];
  int32_T c20_i19;
  int32_T c20_i20;
  int32_T c20_i21;
  real_T c20_u[62];
  const mxArray *c20_y = NULL;
  SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc20_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c20_mxArrayOutData = NULL;
  c20_i16 = 0;
  for (c20_i17 = 0; c20_i17 < 31; c20_i17++) {
    for (c20_i18 = 0; c20_i18 < 2; c20_i18++) {
      c20_b_inData[c20_i18 + c20_i16] = (*(real_T (*)[62])c20_inData)[c20_i18 +
        c20_i16];
    }

    c20_i16 += 2;
  }

  c20_i19 = 0;
  for (c20_i20 = 0; c20_i20 < 31; c20_i20++) {
    for (c20_i21 = 0; c20_i21 < 2; c20_i21++) {
      c20_u[c20_i21 + c20_i19] = c20_b_inData[c20_i21 + c20_i19];
    }

    c20_i19 += 2;
  }

  c20_y = NULL;
  sf_mex_assign(&c20_y, sf_mex_create("y", c20_u, 0, 0U, 1U, 0U, 2, 2, 31),
                FALSE);
  sf_mex_assign(&c20_mxArrayOutData, c20_y, FALSE);
  return c20_mxArrayOutData;
}

static void c20_d_emlrt_marshallIn(SFc20_Hquad_control_LIB_MPCInstanceStruct
  *chartInstance, const mxArray *c20_u, const emlrtMsgIdentifier *c20_parentId,
  real_T c20_y[62])
{
  real_T c20_dv2[62];
  int32_T c20_i22;
  sf_mex_import(c20_parentId, sf_mex_dup(c20_u), c20_dv2, 1, 0, 0U, 1, 0U, 2, 2,
                31);
  for (c20_i22 = 0; c20_i22 < 62; c20_i22++) {
    c20_y[c20_i22] = c20_dv2[c20_i22];
  }

  sf_mex_destroy(&c20_u);
}

static void c20_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c20_mxArrayInData, const char_T *c20_varName, void *c20_outData)
{
  const mxArray *c20_X_ref_temp;
  const char_T *c20_identifier;
  emlrtMsgIdentifier c20_thisId;
  real_T c20_y[62];
  int32_T c20_i23;
  int32_T c20_i24;
  int32_T c20_i25;
  SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc20_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c20_X_ref_temp = sf_mex_dup(c20_mxArrayInData);
  c20_identifier = c20_varName;
  c20_thisId.fIdentifier = c20_identifier;
  c20_thisId.fParent = NULL;
  c20_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c20_X_ref_temp), &c20_thisId,
    c20_y);
  sf_mex_destroy(&c20_X_ref_temp);
  c20_i23 = 0;
  for (c20_i24 = 0; c20_i24 < 31; c20_i24++) {
    for (c20_i25 = 0; c20_i25 < 2; c20_i25++) {
      (*(real_T (*)[62])c20_outData)[c20_i25 + c20_i23] = c20_y[c20_i25 +
        c20_i23];
    }

    c20_i23 += 2;
  }

  sf_mex_destroy(&c20_mxArrayInData);
}

const mxArray *sf_c20_Hquad_control_LIB_MPC_get_eml_resolved_functions_info(void)
{
  const mxArray *c20_nameCaptureInfo;
  c20_ResolvedFunctionInfo c20_info[22];
  const mxArray *c20_m0 = NULL;
  int32_T c20_i26;
  c20_ResolvedFunctionInfo *c20_r0;
  c20_nameCaptureInfo = NULL;
  c20_nameCaptureInfo = NULL;
  c20_info_helper(c20_info);
  sf_mex_assign(&c20_m0, sf_mex_createstruct("nameCaptureInfo", 1, 22), FALSE);
  for (c20_i26 = 0; c20_i26 < 22; c20_i26++) {
    c20_r0 = &c20_info[c20_i26];
    sf_mex_addfield(c20_m0, sf_mex_create("nameCaptureInfo", c20_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c20_r0->context)), "context", "nameCaptureInfo",
                    c20_i26);
    sf_mex_addfield(c20_m0, sf_mex_create("nameCaptureInfo", c20_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c20_r0->name)), "name", "nameCaptureInfo",
                    c20_i26);
    sf_mex_addfield(c20_m0, sf_mex_create("nameCaptureInfo",
      c20_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c20_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c20_i26);
    sf_mex_addfield(c20_m0, sf_mex_create("nameCaptureInfo", c20_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c20_r0->resolved)), "resolved",
                    "nameCaptureInfo", c20_i26);
    sf_mex_addfield(c20_m0, sf_mex_create("nameCaptureInfo", &c20_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c20_i26);
    sf_mex_addfield(c20_m0, sf_mex_create("nameCaptureInfo", &c20_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c20_i26);
    sf_mex_addfield(c20_m0, sf_mex_create("nameCaptureInfo",
      &c20_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c20_i26);
    sf_mex_addfield(c20_m0, sf_mex_create("nameCaptureInfo",
      &c20_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c20_i26);
  }

  sf_mex_assign(&c20_nameCaptureInfo, c20_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c20_nameCaptureInfo);
  return c20_nameCaptureInfo;
}

static void c20_info_helper(c20_ResolvedFunctionInfo c20_info[22])
{
  c20_info[0].context = "";
  c20_info[0].name = "mtimes";
  c20_info[0].dominantType = "double";
  c20_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c20_info[0].fileTimeLo = 1289519692U;
  c20_info[0].fileTimeHi = 0U;
  c20_info[0].mFileTimeLo = 0U;
  c20_info[0].mFileTimeHi = 0U;
  c20_info[1].context = "";
  c20_info[1].name = "reshape";
  c20_info[1].dominantType = "double";
  c20_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m";
  c20_info[1].fileTimeLo = 1286818768U;
  c20_info[1].fileTimeHi = 0U;
  c20_info[1].mFileTimeLo = 0U;
  c20_info[1].mFileTimeHi = 0U;
  c20_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m";
  c20_info[2].name = "eml_index_class";
  c20_info[2].dominantType = "";
  c20_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c20_info[2].fileTimeLo = 1323170578U;
  c20_info[2].fileTimeHi = 0U;
  c20_info[2].mFileTimeLo = 0U;
  c20_info[2].mFileTimeHi = 0U;
  c20_info[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m!reshape_varargin_to_size";
  c20_info[3].name = "eml_index_class";
  c20_info[3].dominantType = "";
  c20_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c20_info[3].fileTimeLo = 1323170578U;
  c20_info[3].fileTimeHi = 0U;
  c20_info[3].mFileTimeLo = 0U;
  c20_info[3].mFileTimeHi = 0U;
  c20_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m!varargin_nempty";
  c20_info[4].name = "eml_index_class";
  c20_info[4].dominantType = "";
  c20_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c20_info[4].fileTimeLo = 1323170578U;
  c20_info[4].fileTimeHi = 0U;
  c20_info[4].mFileTimeLo = 0U;
  c20_info[4].mFileTimeHi = 0U;
  c20_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m!varargin_nempty";
  c20_info[5].name = "eml_index_plus";
  c20_info[5].dominantType = "double";
  c20_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c20_info[5].fileTimeLo = 1286818778U;
  c20_info[5].fileTimeHi = 0U;
  c20_info[5].mFileTimeLo = 0U;
  c20_info[5].mFileTimeHi = 0U;
  c20_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c20_info[6].name = "eml_index_class";
  c20_info[6].dominantType = "";
  c20_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c20_info[6].fileTimeLo = 1323170578U;
  c20_info[6].fileTimeHi = 0U;
  c20_info[6].mFileTimeLo = 0U;
  c20_info[6].mFileTimeHi = 0U;
  c20_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m!reshape_varargin_to_size";
  c20_info[7].name = "eml_assert_valid_size_arg";
  c20_info[7].dominantType = "double";
  c20_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c20_info[7].fileTimeLo = 1286818694U;
  c20_info[7].fileTimeHi = 0U;
  c20_info[7].mFileTimeLo = 0U;
  c20_info[7].mFileTimeHi = 0U;
  c20_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral";
  c20_info[8].name = "isinf";
  c20_info[8].dominantType = "double";
  c20_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m";
  c20_info[8].fileTimeLo = 1286818760U;
  c20_info[8].fileTimeHi = 0U;
  c20_info[8].mFileTimeLo = 0U;
  c20_info[8].mFileTimeHi = 0U;
  c20_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!numel_for_size";
  c20_info[9].name = "mtimes";
  c20_info[9].dominantType = "double";
  c20_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c20_info[9].fileTimeLo = 1289519692U;
  c20_info[9].fileTimeHi = 0U;
  c20_info[9].mFileTimeLo = 0U;
  c20_info[9].mFileTimeHi = 0U;
  c20_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c20_info[10].name = "eml_index_class";
  c20_info[10].dominantType = "";
  c20_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c20_info[10].fileTimeLo = 1323170578U;
  c20_info[10].fileTimeHi = 0U;
  c20_info[10].mFileTimeLo = 0U;
  c20_info[10].mFileTimeHi = 0U;
  c20_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c20_info[11].name = "intmax";
  c20_info[11].dominantType = "char";
  c20_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c20_info[11].fileTimeLo = 1311255316U;
  c20_info[11].fileTimeHi = 0U;
  c20_info[11].mFileTimeLo = 0U;
  c20_info[11].mFileTimeHi = 0U;
  c20_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m!reshape_varargin_to_size";
  c20_info[12].name = "eml_index_prod";
  c20_info[12].dominantType = "coder.internal.indexInt";
  c20_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_prod.m";
  c20_info[12].fileTimeLo = 1286818780U;
  c20_info[12].fileTimeHi = 0U;
  c20_info[12].mFileTimeLo = 0U;
  c20_info[12].mFileTimeHi = 0U;
  c20_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_prod.m";
  c20_info[13].name = "eml_index_class";
  c20_info[13].dominantType = "";
  c20_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c20_info[13].fileTimeLo = 1323170578U;
  c20_info[13].fileTimeHi = 0U;
  c20_info[13].mFileTimeLo = 0U;
  c20_info[13].mFileTimeHi = 0U;
  c20_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_prod.m";
  c20_info[14].name = "eml_int_forloop_overflow_check";
  c20_info[14].dominantType = "";
  c20_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c20_info[14].fileTimeLo = 1346510340U;
  c20_info[14].fileTimeHi = 0U;
  c20_info[14].mFileTimeLo = 0U;
  c20_info[14].mFileTimeHi = 0U;
  c20_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c20_info[15].name = "intmax";
  c20_info[15].dominantType = "char";
  c20_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c20_info[15].fileTimeLo = 1311255316U;
  c20_info[15].fileTimeHi = 0U;
  c20_info[15].mFileTimeLo = 0U;
  c20_info[15].mFileTimeHi = 0U;
  c20_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_prod.m";
  c20_info[16].name = "eml_index_times";
  c20_info[16].dominantType = "coder.internal.indexInt";
  c20_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c20_info[16].fileTimeLo = 1286818780U;
  c20_info[16].fileTimeHi = 0U;
  c20_info[16].mFileTimeLo = 0U;
  c20_info[16].mFileTimeHi = 0U;
  c20_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c20_info[17].name = "eml_index_class";
  c20_info[17].dominantType = "";
  c20_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c20_info[17].fileTimeLo = 1323170578U;
  c20_info[17].fileTimeHi = 0U;
  c20_info[17].mFileTimeLo = 0U;
  c20_info[17].mFileTimeHi = 0U;
  c20_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m!reshape_varargin_to_size";
  c20_info[18].name = "eml_index_rdivide";
  c20_info[18].dominantType = "coder.internal.indexInt";
  c20_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_rdivide.m";
  c20_info[18].fileTimeLo = 1286818780U;
  c20_info[18].fileTimeHi = 0U;
  c20_info[18].mFileTimeLo = 0U;
  c20_info[18].mFileTimeHi = 0U;
  c20_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_rdivide.m";
  c20_info[19].name = "eml_index_class";
  c20_info[19].dominantType = "";
  c20_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c20_info[19].fileTimeLo = 1323170578U;
  c20_info[19].fileTimeHi = 0U;
  c20_info[19].mFileTimeLo = 0U;
  c20_info[19].mFileTimeHi = 0U;
  c20_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m";
  c20_info[20].name = "eml_scalar_eg";
  c20_info[20].dominantType = "double";
  c20_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c20_info[20].fileTimeLo = 1286818796U;
  c20_info[20].fileTimeHi = 0U;
  c20_info[20].mFileTimeLo = 0U;
  c20_info[20].mFileTimeHi = 0U;
  c20_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m";
  c20_info[21].name = "eml_int_forloop_overflow_check";
  c20_info[21].dominantType = "";
  c20_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c20_info[21].fileTimeLo = 1346510340U;
  c20_info[21].fileTimeHi = 0U;
  c20_info[21].mFileTimeLo = 0U;
  c20_info[21].mFileTimeHi = 0U;
}

static const mxArray *c20_d_sf_marshallOut(void *chartInstanceVoid, void
  *c20_inData)
{
  const mxArray *c20_mxArrayOutData = NULL;
  int32_T c20_u;
  const mxArray *c20_y = NULL;
  SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc20_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c20_mxArrayOutData = NULL;
  c20_u = *(int32_T *)c20_inData;
  c20_y = NULL;
  sf_mex_assign(&c20_y, sf_mex_create("y", &c20_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c20_mxArrayOutData, c20_y, FALSE);
  return c20_mxArrayOutData;
}

static int32_T c20_e_emlrt_marshallIn(SFc20_Hquad_control_LIB_MPCInstanceStruct *
  chartInstance, const mxArray *c20_u, const emlrtMsgIdentifier *c20_parentId)
{
  int32_T c20_y;
  int32_T c20_i27;
  sf_mex_import(c20_parentId, sf_mex_dup(c20_u), &c20_i27, 1, 6, 0U, 0, 0U, 0);
  c20_y = c20_i27;
  sf_mex_destroy(&c20_u);
  return c20_y;
}

static void c20_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c20_mxArrayInData, const char_T *c20_varName, void *c20_outData)
{
  const mxArray *c20_b_sfEvent;
  const char_T *c20_identifier;
  emlrtMsgIdentifier c20_thisId;
  int32_T c20_y;
  SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc20_Hquad_control_LIB_MPCInstanceStruct *)chartInstanceVoid;
  c20_b_sfEvent = sf_mex_dup(c20_mxArrayInData);
  c20_identifier = c20_varName;
  c20_thisId.fIdentifier = c20_identifier;
  c20_thisId.fParent = NULL;
  c20_y = c20_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c20_b_sfEvent),
    &c20_thisId);
  sf_mex_destroy(&c20_b_sfEvent);
  *(int32_T *)c20_outData = c20_y;
  sf_mex_destroy(&c20_mxArrayInData);
}

static uint8_T c20_f_emlrt_marshallIn(SFc20_Hquad_control_LIB_MPCInstanceStruct *
  chartInstance, const mxArray *c20_b_is_active_c20_Hquad_control_LIB_MPC, const
  char_T *c20_identifier)
{
  uint8_T c20_y;
  emlrtMsgIdentifier c20_thisId;
  c20_thisId.fIdentifier = c20_identifier;
  c20_thisId.fParent = NULL;
  c20_y = c20_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c20_b_is_active_c20_Hquad_control_LIB_MPC), &c20_thisId);
  sf_mex_destroy(&c20_b_is_active_c20_Hquad_control_LIB_MPC);
  return c20_y;
}

static uint8_T c20_g_emlrt_marshallIn(SFc20_Hquad_control_LIB_MPCInstanceStruct *
  chartInstance, const mxArray *c20_u, const emlrtMsgIdentifier *c20_parentId)
{
  uint8_T c20_y;
  uint8_T c20_u0;
  sf_mex_import(c20_parentId, sf_mex_dup(c20_u), &c20_u0, 1, 3, 0U, 0, 0U, 0);
  c20_y = c20_u0;
  sf_mex_destroy(&c20_u);
  return c20_y;
}

static void init_dsm_address_info(SFc20_Hquad_control_LIB_MPCInstanceStruct
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

void sf_c20_Hquad_control_LIB_MPC_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2239272125U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2199183954U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3916870236U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2334827570U);
}

mxArray *sf_c20_Hquad_control_LIB_MPC_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("tNYoVAWCxd8JSGzubW0QQE");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(62);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c20_Hquad_control_LIB_MPC_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c20_Hquad_control_LIB_MPC(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[18],T\"X_ref\",},{M[8],M[0],T\"is_active_c20_Hquad_control_LIB_MPC\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c20_Hquad_control_LIB_MPC_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
    chartInstance = (SFc20_Hquad_control_LIB_MPCInstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _Hquad_control_LIB_MPCMachineNumber_,
           20,
           1,
           1,
           3,
           0,
           0,
           0,
           0,
           0,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"x_ref");
          _SFD_SET_DATA_PROPS(1,1,1,0,"x_dot_ref");
          _SFD_SET_DATA_PROPS(2,2,0,1,"X_ref");
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
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,172);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c20_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c20_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 62;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c20_sf_marshallOut,(MexInFcnForType)
            c20_sf_marshallIn);
        }

        {
          real_T *c20_x_ref;
          real_T *c20_x_dot_ref;
          real_T (*c20_X_ref)[62];
          c20_X_ref = (real_T (*)[62])ssGetOutputPortSignal(chartInstance->S, 1);
          c20_x_dot_ref = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c20_x_ref = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c20_x_ref);
          _SFD_SET_DATA_VALUE_PTR(1U, c20_x_dot_ref);
          _SFD_SET_DATA_VALUE_PTR(2U, *c20_X_ref);
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
  return "qJGrMMHT6fLmo5l53rPatH";
}

static void sf_opaque_initialize_c20_Hquad_control_LIB_MPC(void
  *chartInstanceVar)
{
  chart_debug_initialization(((SFc20_Hquad_control_LIB_MPCInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c20_Hquad_control_LIB_MPC
    ((SFc20_Hquad_control_LIB_MPCInstanceStruct*) chartInstanceVar);
  initialize_c20_Hquad_control_LIB_MPC
    ((SFc20_Hquad_control_LIB_MPCInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c20_Hquad_control_LIB_MPC(void *chartInstanceVar)
{
  enable_c20_Hquad_control_LIB_MPC((SFc20_Hquad_control_LIB_MPCInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c20_Hquad_control_LIB_MPC(void *chartInstanceVar)
{
  disable_c20_Hquad_control_LIB_MPC((SFc20_Hquad_control_LIB_MPCInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c20_Hquad_control_LIB_MPC(void *chartInstanceVar)
{
  sf_c20_Hquad_control_LIB_MPC((SFc20_Hquad_control_LIB_MPCInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c20_Hquad_control_LIB_MPC
  (SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c20_Hquad_control_LIB_MPC
    ((SFc20_Hquad_control_LIB_MPCInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c20_Hquad_control_LIB_MPC();/* state var info */
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

extern void sf_internal_set_sim_state_c20_Hquad_control_LIB_MPC(SimStruct* S,
  const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c20_Hquad_control_LIB_MPC();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c20_Hquad_control_LIB_MPC
    ((SFc20_Hquad_control_LIB_MPCInstanceStruct*)chartInfo->chartInstance,
     mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c20_Hquad_control_LIB_MPC
  (SimStruct* S)
{
  return sf_internal_get_sim_state_c20_Hquad_control_LIB_MPC(S);
}

static void sf_opaque_set_sim_state_c20_Hquad_control_LIB_MPC(SimStruct* S,
  const mxArray *st)
{
  sf_internal_set_sim_state_c20_Hquad_control_LIB_MPC(S, st);
}

static void sf_opaque_terminate_c20_Hquad_control_LIB_MPC(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc20_Hquad_control_LIB_MPCInstanceStruct*)
                    chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Hquad_control_LIB_MPC_optimization_info();
    }

    finalize_c20_Hquad_control_LIB_MPC
      ((SFc20_Hquad_control_LIB_MPCInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc20_Hquad_control_LIB_MPC
    ((SFc20_Hquad_control_LIB_MPCInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c20_Hquad_control_LIB_MPC(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c20_Hquad_control_LIB_MPC
      ((SFc20_Hquad_control_LIB_MPCInstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c20_Hquad_control_LIB_MPC(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_Hquad_control_LIB_MPC_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      20);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,20,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,20,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,20);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,20,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,20,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,20);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(903719969U));
  ssSetChecksum1(S,(548871801U));
  ssSetChecksum2(S,(799602589U));
  ssSetChecksum3(S,(1507839789U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c20_Hquad_control_LIB_MPC(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c20_Hquad_control_LIB_MPC(SimStruct *S)
{
  SFc20_Hquad_control_LIB_MPCInstanceStruct *chartInstance;
  chartInstance = (SFc20_Hquad_control_LIB_MPCInstanceStruct *)utMalloc(sizeof
    (SFc20_Hquad_control_LIB_MPCInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc20_Hquad_control_LIB_MPCInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c20_Hquad_control_LIB_MPC;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c20_Hquad_control_LIB_MPC;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c20_Hquad_control_LIB_MPC;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c20_Hquad_control_LIB_MPC;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c20_Hquad_control_LIB_MPC;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c20_Hquad_control_LIB_MPC;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c20_Hquad_control_LIB_MPC;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c20_Hquad_control_LIB_MPC;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c20_Hquad_control_LIB_MPC;
  chartInstance->chartInfo.mdlStart = mdlStart_c20_Hquad_control_LIB_MPC;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c20_Hquad_control_LIB_MPC;
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

void c20_Hquad_control_LIB_MPC_method_dispatcher(SimStruct *S, int_T method,
  void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c20_Hquad_control_LIB_MPC(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c20_Hquad_control_LIB_MPC(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c20_Hquad_control_LIB_MPC(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c20_Hquad_control_LIB_MPC_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
