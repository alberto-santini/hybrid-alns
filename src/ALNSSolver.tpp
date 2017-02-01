template<class R> R ALNSSolver::roulette_wheel(std::vector<R> vec) const {
    auto total_score = std::accumulate(
        vec.begin(), vec.end(), 0.0f,
        [] (float tot, const R& el) { return tot + el->get_score(); }
    );
    std::uniform_real_distribution<float> dis(0.0f, total_score);
    auto score_rnd = dis(mt);
    auto score_acc = 0.0f;

    for(auto el : vec) {
        score_acc += el->get_score();
        if(score_acc >= score_rnd) { return el; }
    }

    return vec.back();
}

template<class R> void ALNSSolver::update_score(R method, float amount) {
    if(!method) { return; }
    method->set_score(
        method->get_score() * alns_params.history_weight_in_score_update +
        amount * (1.0f - alns_params.history_weight_in_score_update)
    );
}