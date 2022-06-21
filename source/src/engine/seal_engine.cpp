
// Copyright (C) 2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#include "engine/seal_engine.h"
#include "engine/seal_types.h"
#include "engine/seal_version.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <mutex>
#include <sstream>

// include all benchmarks
#include "benchmarks/bfv/seal_bfv_dot_product_benchmark.h"

//-----------------
// Engine creation
//-----------------

namespace hebench {
namespace cpp {

BaseEngine *createEngine()
{
    if (HEBENCH_API_VERSION_MAJOR != HEBENCH_API_VERSION_NEEDED_MAJOR
        || HEBENCH_API_VERSION_MINOR != HEBENCH_API_VERSION_NEEDED_MINOR
        || HEBENCH_API_VERSION_REVISION < HEBENCH_API_VERSION_NEEDED_REVISION
        //|| std::strcmp(HEBENCH_API_VERSION_BUILD, HEBENCH_API_VERSION_NEEDED_BUILD) != 0
    )
    {
        std::stringstream ss;
        ss << "Critical: Invalid HEBench API version detected. Required: "
           << HEBENCH_API_VERSION_NEEDED_MAJOR << "." << HEBENCH_API_VERSION_NEEDED_MINOR << "." << HEBENCH_API_VERSION_NEEDED_REVISION
           << ", but " << HEBENCH_API_VERSION_MAJOR << "." << HEBENCH_API_VERSION_MINOR << "." << HEBENCH_API_VERSION_REVISION
           << " received.";
        throw hebench::cpp::HEBenchError(HEBERROR_MSG(ss.str()),
                                         HEBENCH_ECODE_CRITICAL_ERROR);
    } // end if

    return SEALEngine::create();
}

void destroyEngine(BaseEngine *p)
{
    SEALEngine *_p = dynamic_cast<SEALEngine *>(p);
    SEALEngine::destroy(_p);
}

} // namespace cpp
} // namespace hebench

//---------------------
// class SEALEngine
//---------------------

SEALEngine *SEALEngine::create()
{
    SEALEngine *p_retval = new SEALEngine();
    p_retval->init();
    return p_retval;
}

void SEALEngine::destroy(SEALEngine *p)
{
    if (p)
        delete p;
}

SEALEngine::SEALEngine()
{
}

SEALEngine::~SEALEngine()
{
}

void SEALEngine::init()
{
    // add any new error codes

    addErrorCode(HEBSEAL_ECODE_SEAL_ERROR, "SEAL error");

    // add supported schemes

    addSchemeName(HEBENCH_HE_SCHEME_BFV, "BFV");

    // add supported security
    addSecurityName(HEBENCH_HE_SECURITY_128, "128 bits");

    // add the all benchmark descriptors: only a benchmark per submission allowed
    addBenchmarkDescription(
        std::make_shared<sbe::bfv::DotProductBenchmarkDescription>(hebench::APIBridge::Category::Offline));
}
