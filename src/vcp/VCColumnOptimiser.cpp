//
// Created by alberto on 04/12/16.
//

#include "VCColumnOptimiser.h"

#ifndef IL_STD
    #define IL_STD
#endif

#include <cstring>
#include <ilcplex/ilocplex.h>


Colouring* VCColumnOptimiser::optimise(const ColumnPool& columns) const {
    IloEnv env;
    IloModel model(env);

    std::map<uint32_t, ColumnPool::const_iterator> column_index_to_stable_set;
    uint32_t n = instance.num_vertices;
    uint32_t cid = 0u;

    IloObjective obj = IloMinimize(env);
    IloNumVarArray x(env, columns.size());
    IloRangeArray cover(env, n);

    for(auto v = 0u; v < n; ++v) {
        cover[v] = IloRange(env, 1, IloInfinity);
    }

    for(auto it = columns.begin(); it != columns.end(); ++it) {
        IloNumColumn cplex_col = obj(1);

        for(auto v = 0u; v < n; ++v) {
            cplex_col += cover[v]((*it)[v]);
        }

        x[cid] = IloNumVar(cplex_col, 0, 1, IloNumVar::Bool);
        column_index_to_stable_set[cid] = it;
        ++cid;

        cplex_col.end();
    }

    model.add(x);
    model.add(cover);
    model.add(obj);

    IloCplex cplex(model);
    cplex.setOut(env.getNullStream());
    cplex.setError(env.getNullStream());
    cplex.setParam(IloCplex::Threads, 4);
    cplex.setParam(IloCplex::Param::Parallel, IloCplex::Opportunistic);
    cplex.setParam(IloCplex::RootAlg, IloCplex::Concurrent);
    cplex.setParam(IloCplex::TiLim, timeout);

    IloBool solved;

    try {
        solved = cplex.solve();
    } catch(const IloException& e) {
        return nullptr;
    }

    if(!solved) { return nullptr; }
    std::vector<Column> solution_cols;

    for(auto i = 0u; i < columns.size(); ++i) {
        if(cplex.getValue(x[i]) > .5) {
            solution_cols.push_back(*column_index_to_stable_set[i]);
        }
    }

    Colouring* solution = new Colouring{instance};
    solution->from_columns(solution_cols);

    env.end();

    return solution;
}
