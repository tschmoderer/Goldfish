#pragma once

#include <memory>
#include <chrono>
#include <thread>
#include <condition_variable>
#include <mutex>

#include "protocol.hpp"
#include "position.hpp"
#include "movegenerator.hpp"
#include "evaluation.hpp"
#include "tt.hpp"

namespace goldfish {

/**
 * This class implements our search in a separate thread to keep the main
 * thread available for more commands.
 */
class Search {
public:
    explicit Search(Protocol &protocol);

    void new_depth_search(Position &position, Depth search_depth);

    void new_nodes_search(Position &position, uint64_t search_nodes);

    void new_time_search(Position &position, uint64_t search_time);

    void new_infinite_search(Position &position);

    void new_clock_search(Position &position,
                          uint64_t white_time_left, uint64_t white_time_increment, uint64_t black_time_left,
                          uint64_t black_time_increment, int moves_to_go);

    void new_ponder_search(Position &position,
                           uint64_t white_time_left, uint64_t white_time_increment, uint64_t black_time_left,
                           uint64_t black_time_increment, int moves_to_go);

    void reset();

    void start();

    void stop();

    void ponderhit();

    void quit();

    void wait_for_finished();

    void run();

    uint64_t get_total_nodes();

private:
    /**
     * This is our search timer for time & clock & ponder searches.
     */
    class Timer {
    public:
        Timer(bool &timer_stopped, bool &do_time_management, Depth &current_depth, const Depth &initial_depth, bool &abort);

        void start(uint64_t search_time);

        void stop();

    private:
        std::mutex mutex;
        std::condition_variable condition;
        std::thread thread;

        bool &timer_stopped;
        bool &do_time_management;
        Depth &current_depth;
        const Depth &initial_depth;

        bool &abort;

        void run(uint64_t search_time);
    };

    class Semaphore {
    public:
        explicit Semaphore(int permits);

        void acquire();

        void release();

        void drain_permits();

    private:
        int permits;
        std::mutex mutex;
        std::condition_variable condition;
    };

    std::thread thread;
    Semaphore wakeup_signal;
    Semaphore run_signal;
    Semaphore stop_signal;
    Semaphore finished_signal;
    std::recursive_mutex sync;
    Protocol &protocol;
    bool running = false;
    bool shutdown = false;

    Position position;

    // We will store a MoveGenerator for each ply so we don't have to create them
    // in search. (which is expensive)
    std::array<MoveGenerator, Depth::MAX_PLY> move_generators;

    // Depths search
    Depth search_depth;

    // Nodes search
    uint64_t search_nodes;

    // Time & Clock & Ponder search
    uint64_t search_time;
    Timer timer;
    bool timer_stopped;
    bool run_timer;
    bool do_time_management;

    // Search parameters
    MoveList<RootEntry> root_moves;
    bool abort;
    uint64_t total_nodes;
    const Depth initial_depth = Depth(1);
    Depth current_depth;
    Depth current_max_depth;
    Move current_move;
    int current_move_number;
    std::array<MoveVariation, Depth::MAX_PLY + 1> pv;

    void check_stop_conditions();

    void update_search(int ply);

    void search_root(Depth depth, int alpha, int beta);

    int search(Depth depth, int alpha, int beta, int ply);

    int quiescent(Depth depth, int alpha, int beta, int ply);

    void save_pv(Move move, MoveVariation &src, MoveVariation &dest);
};

}
