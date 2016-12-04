//
// Created by alberto on 24/11/16.
//

#ifndef HYBRID_ALNS_DESTROYMETHODS_H
#define HYBRID_ALNS_DESTROYMETHODS_H

#include "../DestroyMethod.h"
#include "VCInstance.h"
#include "Colouring.h"

class EmptySmallestColour : public DestroyMethod {
    const VCInstance& instance;

public:
    EmptySmallestColour(const Params& alns_params, const VCInstance& instance) : DestroyMethod{alns_params, "empty smallest colour"}, instance{instance} {}
    ~EmptySmallestColour() {}

    Colouring* operator()(const Solution *const solution) const;
};

class EmptyNSmallestColours : public DestroyMethod {
    const VCInstance& instance;

public:
    EmptyNSmallestColours(const Params& alns_params, const VCInstance& instance) : DestroyMethod{alns_params, "empty n smallest colours"}, instance{instance} {}
    ~EmptyNSmallestColours() {}

    Colouring* operator()(const Solution *const solution) const;
};

class EmptySmallestColourRouletteWheel : public DestroyMethod {
    const VCInstance& instance;

public:
    EmptySmallestColourRouletteWheel(const Params& alns_params, const VCInstance& instance) : DestroyMethod{alns_params, "empty smallest colour roulette wheel"}, instance{instance} {}
    ~EmptySmallestColourRouletteWheel() {}

    Colouring* operator()(const Solution *const solution) const;
};

class EmptyRandomColour : public DestroyMethod {
    const VCInstance& instance;

public:
    EmptyRandomColour(const Params& alns_params, const VCInstance& instance) : DestroyMethod{alns_params, "empty random colour"}, instance{instance} {}
    ~EmptyRandomColour() {}

    Colouring* operator()(const Solution *const solution) const;
};

class EmptyNRandomColours : public DestroyMethod {
    const VCInstance& instance;

public:
    EmptyNRandomColours(const Params& alns_params, const VCInstance& instance) : DestroyMethod{alns_params, "empty n random colours"}, instance{instance} {}
    ~EmptyNRandomColours() {}

    Colouring* operator()(const Solution *const solution) const;
};

class EmptyColourWithSmallestColourDegree : public DestroyMethod {
    const VCInstance& instance;

public:
    EmptyColourWithSmallestColourDegree(const Params& alns_params, const VCInstance& instance) : DestroyMethod{alns_params, "empty smallest colour degree"}, instance{instance} {}
    ~EmptyColourWithSmallestColourDegree() {}

    Colouring* operator()(const Solution *const solution) const;
};

class EmptyNColoursWithSmallestColourDegree : public DestroyMethod {
    const VCInstance& instance;

public:
    EmptyNColoursWithSmallestColourDegree(const Params& alns_params, const VCInstance& instance) : DestroyMethod{alns_params, "empty n smallest colour degrees"}, instance{instance} {}
    ~EmptyNColoursWithSmallestColourDegree() {}

    Colouring* operator()(const Solution *const solution) const;
};

class EmptyColourWithSmallestColourDegreeRouletteWheel : public DestroyMethod {
    const VCInstance& instance;

public:
    EmptyColourWithSmallestColourDegreeRouletteWheel(const Params& alns_params, const VCInstance& instance) : DestroyMethod{alns_params, "empty smallest colour degree roulette wheel"}, instance{instance} {}
    ~EmptyColourWithSmallestColourDegreeRouletteWheel() {}

    Colouring* operator()(const Solution *const solution) const;
};

class RemoveRandomVertexFromRandomColour : public DestroyMethod {
    const VCInstance& instance;

public:
    RemoveRandomVertexFromRandomColour(const Params& alns_params, const VCInstance& instance) : DestroyMethod{alns_params, "remove random vertex from random colour"}, instance{instance} {}
    ~RemoveRandomVertexFromRandomColour() {}

    Colouring* operator()(const Solution *const solution) const;
};

class RemoveRandomVertexFromSmallestColour : public DestroyMethod {
    const VCInstance& instance;

public:
    RemoveRandomVertexFromSmallestColour(const Params& alns_params, const VCInstance& instance) : DestroyMethod{alns_params, "remove random vertex from smallest colour"}, instance{instance} {}
    ~RemoveRandomVertexFromSmallestColour() {}

    Colouring* operator()(const Solution *const solution) const;
};

class RemoveRandomVertexFromBiggestColour : public DestroyMethod {
    const VCInstance& instance;

public:
    RemoveRandomVertexFromBiggestColour(const Params& alns_params, const VCInstance& instance) : DestroyMethod{alns_params, "remove random vertex from biggest colour"}, instance{instance} {}
    ~RemoveRandomVertexFromBiggestColour() {}

    Colouring* operator()(const Solution *const solution) const;
};

class UncolourVertexWithSmallestDegree : public DestroyMethod {
    const VCInstance& instance;

public:
    UncolourVertexWithSmallestDegree(const Params& alns_params, const VCInstance& instance) : DestroyMethod{alns_params, "uncolour vertex with smallest colour degree"}, instance{instance} {}
    ~UncolourVertexWithSmallestDegree() {}

    Colouring* operator()(const Solution *const solution) const;
};

class UncolourVertexWithSmallestColourDegree : public DestroyMethod {
    const VCInstance& instance;

public:
    UncolourVertexWithSmallestColourDegree(const Params& alns_params, const VCInstance& instance) : DestroyMethod{alns_params, "uncolour vertex with smallest colour degree"}, instance{instance} {}
    ~UncolourVertexWithSmallestColourDegree() {}

    Colouring* operator()(const Solution *const solution) const;
};

class UncolourVertexWithSmallestColourDegreeRouletteWheel : public DestroyMethod {
    const VCInstance& instance;

public:
    UncolourVertexWithSmallestColourDegreeRouletteWheel(const Params& alns_params, const VCInstance& instance) : DestroyMethod{alns_params, "uncolour vertex with smallest colour degree roulette wheel"}, instance{instance} {}
    ~UncolourVertexWithSmallestColourDegreeRouletteWheel() {}

    Colouring* operator()(const Solution *const solution) const;
};

class UncolourVertexWithLargestDegree : public DestroyMethod {
    const VCInstance& instance;

public:
    UncolourVertexWithLargestDegree(const Params& alns_params, const VCInstance& instance) : DestroyMethod{alns_params, "uncolour vertex with largest colour degree"}, instance{instance} {}
    ~UncolourVertexWithLargestDegree() {}

    Colouring* operator()(const Solution *const solution) const;
};

class UncolourVertexWithLargestColourDegree : public DestroyMethod {
    const VCInstance& instance;

public:
    UncolourVertexWithLargestColourDegree(const Params& alns_params, const VCInstance& instance) : DestroyMethod{alns_params, "uncolour vertex with largest colour degree"}, instance{instance} {}
    ~UncolourVertexWithLargestColourDegree() {}

    Colouring* operator()(const Solution *const solution) const;
};

class UncolourVertexWithLargestColourDegreeRouletteWheel : public DestroyMethod {
    const VCInstance& instance;

public:
    UncolourVertexWithLargestColourDegreeRouletteWheel(const Params& alns_params, const VCInstance& instance) : DestroyMethod{alns_params, "uncolour vertex with largest colour degree roulette wheel"}, instance{instance} {}
    ~UncolourVertexWithLargestColourDegreeRouletteWheel() {}

    Colouring* operator()(const Solution *const solution) const;
};

#endif //HYBRID_ALNS_DESTROYMETHODS_H
