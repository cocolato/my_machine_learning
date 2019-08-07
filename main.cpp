#include "src/classify.h"
#include "src/qlearning.h"
#include "src/ants.h"
#include "src/kpga.h"
#include <boost/progress.hpp>

using namespace std;

int main(){
    boost::progress_timer p_time;
//    QLearning my_ql;
//    my_ql.Run();
//    ants a;
//    a.Run();
    kpGA ga;
    ga.Run();





    return 0;
}

