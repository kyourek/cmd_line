#include "ucmdtests.h"

uc_TEST_RUNNER(ucmd,
    &ucTestGroup_ucArgOpt,
    &ucTestGroup_ucArgOptOwner,
    &ucTestGroup_ucArgTokOwner,
    &ucTestGroup_ucArgTok,
    &ucTestGroup_ucBool,
    &ucTestGroup_ucParser,
    &ucTestGroup_ucCmdTok,
    &ucTestGroup_ucOpt,
    &ucTestGroup_ucSwitchOpt,
    &ucTestGroup_ucSwitchTok,
    &ucTestGroup_ucTok,
    &ucTestGroup_ucApp,
    &ucTestGroup_ucCmdOpt,
    &ucTestGroup_ucCmd)
