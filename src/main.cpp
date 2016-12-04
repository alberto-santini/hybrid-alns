#include <iostream>
#include <memory>
#include "Params.h"
#include "acceptance/WorseAccept.h"
#include "ALNSSolver.h"
#include "vcp/VCInstance.h"
#include "vcp/GreedyColour.h"
#include "vcp/DestroyMethods.h"
#include "vcp/RepairMethods.h"
#include "vcp/VCLocalSearch.h"
#include "vcp/VCColumnOptimiser.h"

int main(int argc, char** argv) {
    assert(argc == 2);
    std::string instance{argv[1]};

    VCInstance vci{instance, "../params/vcp.json"};
    VCColumnOptimiser vccopt{vci};
    GreedyColour gc{vci};
    Colouring initial = gc.get_colouring();

    std::cout << "Initial colouring: ";
    initial.print_summary();

    Params alns_params{"../params/alns.json"};
    WorseAccept wa{"../params/acceptance.json", alns_params};
    VCLocalSearch ls{};
    ALNSSolver solver{alns_params, &wa, &vccopt, &ls};

    solver.add_destroy_method(new EmptySmallestColour{alns_params, vci});
    solver.add_destroy_method(new EmptyNSmallestColours{alns_params, vci});
    solver.add_destroy_method(new EmptySmallestColourRouletteWheel{alns_params, vci});
    solver.add_destroy_method(new EmptyRandomColour{alns_params, vci});
    solver.add_destroy_method(new EmptyNRandomColours{alns_params, vci});
    solver.add_destroy_method(new EmptyColourWithSmallestColourDegree{alns_params, vci});
    solver.add_destroy_method(new EmptyNColoursWithSmallestColourDegree{alns_params, vci});
    solver.add_destroy_method(new RemoveRandomVertexFromRandomColour{alns_params, vci});
    solver.add_destroy_method(new RemoveRandomVertexFromSmallestColour{alns_params, vci});
    solver.add_destroy_method(new RemoveRandomVertexFromBiggestColour{alns_params, vci});
    solver.add_destroy_method(new UncolourVertexWithSmallestDegree{alns_params, vci});
    solver.add_destroy_method(new UncolourVertexWithSmallestColourDegree{alns_params, vci});
    solver.add_destroy_method(new UncolourVertexWithSmallestColourDegreeRouletteWheel{alns_params, vci});
    solver.add_destroy_method(new UncolourVertexWithLargestDegree{alns_params, vci});
    solver.add_destroy_method(new UncolourVertexWithLargestColourDegree{alns_params, vci});
    solver.add_destroy_method(new UncolourVertexWithLargestColourDegreeRouletteWheel{alns_params, vci});
    solver.add_repair_method(new GreedyRecolourDegreeAsc{alns_params, vci});
    solver.add_repair_method(new GreedyRecolourDegreeDesc{alns_params, vci});
    solver.add_repair_method(new GreedyRecolourColourDegreeAsc{alns_params, vci});
    solver.add_repair_method(new GreedyRecolourColourDegreeDesc{alns_params, vci});
    solver.add_repair_method(new MWSSRecolour{alns_params, vci});
    solver.add_repair_method(new GreedyAndMWSSRecolour{alns_params, vci});

    Solution* sol = solver.solve(&initial);

    std::cout << "Final colouring: ";
    sol->print_summary();

    delete sol;

    return 0;
}