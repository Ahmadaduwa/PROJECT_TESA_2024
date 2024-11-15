/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: _coder_predictSignal_info.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 10:15:10
 */

/* Include Files */
#include "_coder_predictSignal_info.h"
#include "emlrt.h"
#include "tmwtypes.h"

/* Function Declarations */
static const mxArray *c_emlrtMexFcnResolvedFunctionsI(void);

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : const mxArray *
 */
static const mxArray *c_emlrtMexFcnResolvedFunctionsI(void)
{
  const mxArray *nameCaptureInfo;
  const char_T *data[5] = {
      "789ce554cd4ac34010de888a206a4f9e3c8a172158f1a77a8d0a511b0a8d8a7445b7c9aa"
      "c1fda9bbdb12dfc09b578fbe8237f139bcf9225e04dbb4e9cf4248b1"
      "1051e7323bf966f7fb66363bc0b08b06006016b4ed69baed673a71aee3c7c0a0e9b8a1e5"
      "1983e960028c0fec8bf1878ef738533854ed80218abb3b7d4e038698",
      "72ef6a18082c3969603f422e0382dd80e2727fe0b422bad707758316d45a5bd7d8bb29d7"
      "2910d7b2a790f407dd7e5c24d43b9ed20fddf47ee879ff85eff19b7c"
      "f1f9f914be18af1c9ded6ec3132e6ece6de61124252c095c13dcc3cda5122860d83f709c"
      "22f7313129529ace8b041d7343ead47d2f7f2af2cf1bef46967c930b",
      "f2234bbed87e8a2f4c386fd8ff6c3e812fa7e105bc4942bc5eb83dd83a6ed8451e58872a"
      "bfd3d3514ae149d30112e2acce7f49d83f6c1f8f12cecf6978c5b6ce"
      "169bcf90a0aae05c2d42c539a9f2104a859484d10b16f80a2ef7560423c102d6fad67cc4"
      "025a9cd690a79acfdc0f3cc58549fbeab81fb18ea5943a623c9667c6",
      "eacc485c5d05449aae404c5e72417f6efe8e7a9fe514be18afd8ce88f719b50c765b16dd"
      "6676f364fbf52dd3f90ce027c994af637f7d3eef23d7ad23ff44541d"
      "555b3b2d842bab5c58bf7f3e7f01bf55b2d0",
      ""};
  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(&data[0], 3000U, &nameCaptureInfo);
  return nameCaptureInfo;
}

/*
 * Arguments    : void
 * Return Type  : mxArray *
 */
mxArray *emlrtMexFcnProperties(void)
{
  mxArray *xEntryPoints;
  mxArray *xInputs;
  mxArray *xResult;
  const char_T *propFieldName[9] = {"Version",
                                    "ResolvedFunctions",
                                    "Checksum",
                                    "EntryPoints",
                                    "CoverageInfo",
                                    "IsPolymorphic",
                                    "PropertyList",
                                    "UUID",
                                    "ClassEntryPointIsHandle"};
  const char_T *epFieldName[8] = {
      "QualifiedName",    "NumberOfInputs", "NumberOfOutputs", "ConstantInputs",
      "ResolvedFilePath", "TimeStamp",      "Constructor",     "Visible"};
  xEntryPoints =
      emlrtCreateStructMatrix(1, 1, 8, (const char_T **)&epFieldName[0]);
  xInputs = emlrtCreateLogicalMatrix(1, 1);
  emlrtSetField(xEntryPoints, 0, "QualifiedName",
                emlrtMxCreateString("predictSignal"));
  emlrtSetField(xEntryPoints, 0, "NumberOfInputs",
                emlrtMxCreateDoubleScalar(1.0));
  emlrtSetField(xEntryPoints, 0, "NumberOfOutputs",
                emlrtMxCreateDoubleScalar(1.0));
  emlrtSetField(xEntryPoints, 0, "ConstantInputs", xInputs);
  emlrtSetField(
      xEntryPoints, 0, "ResolvedFilePath",
      emlrtMxCreateString("E:\\Work_Inclass\\Preprocess\\predictSignal.m"));
  emlrtSetField(xEntryPoints, 0, "TimeStamp",
                emlrtMxCreateDoubleScalar(739571.425925926));
  emlrtSetField(xEntryPoints, 0, "Constructor",
                emlrtMxCreateLogicalScalar(false));
  emlrtSetField(xEntryPoints, 0, "Visible", emlrtMxCreateLogicalScalar(true));
  xResult =
      emlrtCreateStructMatrix(1, 1, 9, (const char_T **)&propFieldName[0]);
  emlrtSetField(xResult, 0, "Version",
                emlrtMxCreateString("24.2.0.2740171 (R2024b) Update 1"));
  emlrtSetField(xResult, 0, "ResolvedFunctions",
                (mxArray *)c_emlrtMexFcnResolvedFunctionsI());
  emlrtSetField(xResult, 0, "Checksum",
                emlrtMxCreateString("cMxZLswD4pNVDS9OZdCdt"));
  emlrtSetField(xResult, 0, "EntryPoints", xEntryPoints);
  return xResult;
}

/*
 * File trailer for _coder_predictSignal_info.c
 *
 * [EOF]
 */
