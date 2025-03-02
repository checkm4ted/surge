/*
 * Surge XT - a free and open source hybrid synthesizer,
 * built by Surge Synth Team
 *
 * Learn more at https://surge-synthesizer.github.io/
 *
 * Copyright 2018-2023, various authors, as described in the GitHub
 * transaction log.
 *
 * Surge XT is released under the GNU General Public Licence v3
 * or later (GPL-3.0-or-later). The license is found in the "LICENSE"
 * file in the root of this repository, or at
 * https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * Surge was a commercial product from 2004-2018, copyright and ownership
 * held by Claes Johanson at Vember Audio during that period.
 * Claes made Surge open source in September 2018.
 *
 * All source for Surge XT is available at
 * https://github.com/surge-synthesizer/surge
 */

#ifndef SURGE_SRC_COMMON_DSP_EFFECTS_PARAMETRICEQ3BANDEFFECT_H
#define SURGE_SRC_COMMON_DSP_EFFECTS_PARAMETRICEQ3BANDEFFECT_H
#include "Effect.h"
#include "BiquadFilter.h"
#include "DSPUtils.h"
#include "AllpassFilter.h"

#include <vembertech/lipol.h>

class ParametricEQ3BandEffect : public Effect
{
    lipol_ps_blocksz gain alignas(16);
    lipol_ps_blocksz mix alignas(16);

    float L alignas(16)[BLOCK_SIZE], R alignas(16)[BLOCK_SIZE];

  public:
    enum eq3_params
    {
        eq3_gain1 = 0,
        eq3_freq1,
        eq3_bw1,

        eq3_gain2,
        eq3_freq2,
        eq3_bw2,

        eq3_gain3,
        eq3_freq3,
        eq3_bw3,

        eq3_gain,
        eq3_mix,

        eq3_num_ctrls,
    };

    ParametricEQ3BandEffect(SurgeStorage *storage, FxStorage *fxdata, pdata *pd);
    virtual ~ParametricEQ3BandEffect();
    virtual const char *get_effectname() override { return "EQ"; }
    virtual void init() override;
    virtual void process(float *dataL, float *dataR) override;
    virtual void suspend() override;
    void setvars(bool init);
    virtual void init_ctrltypes() override;
    virtual void init_default_values() override;
    virtual const char *group_label(int id) override;
    virtual int group_label_ypos(int id) override;

    virtual void handleStreamingMismatches(int streamingRevision,
                                           int currentSynthStreamingRevision) override;

  private:
    BiquadFilter band1, band2, band3;
    int bi; // block increment (to keep track of events not occurring every n blocks)
};

#endif // SURGE_SRC_COMMON_DSP_EFFECTS_PARAMETRICEQ3BANDEFFECT_H
