#pragma once

#include <GTEngine.h>
using namespace gte;

class GTTest01Window : public Window3
{
public:
    GTTest01Window(Parameters& parameters);

    virtual void OnIdle() override;

private:
};
