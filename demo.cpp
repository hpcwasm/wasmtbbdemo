// #include <cstdlib>
// #include <exception>
#include <iostream>
#include <iostream>
#include <cstdlib>
// #include <pthread.h>
#include <openvdb/Types.h>
#include <openvdb/openvdb.h>
#include <emscripten/emscripten.h>
#include <emscripten/threading.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>
  
#include <emscripten.h>
// #include <pthread.h>
 
// #ifdef __EMSCRIPTEN_PTHREADS__
//  #error "__EMSCRIPTEN_PTHREADS__"
// #else
// #error " NOT __EMSCRIPTEN_PTHREADS__"
// #endif

#include <openvdb/tools/LevelSetAdvect.h>
#include <openvdb/tools/LevelSetSphere.h>
#include <openvdb/tools/VelocityFields.h>
using namespace std;

// void *PrintHello(void *threadid) {
//    long tid;
//    tid = (long)threadid;
// //    cout << "Hello World! Thread ID, " << tid << endl;
//    pthread_exit(NULL);
// }

int myrun() {

//    pthread_t threads[2];
//    int rc;
//    int i;
   
//    for( i = 0; i < 2; i++ ) {
//     //   cout << "main() : creating thread, " << i << endl;
//       rc = pthread_create(&threads[i], NULL, PrintHello, (void *)i);
      
//       if (rc) {
//         //  cout << "Error:unable to create thread," << rc << endl;
//          exit(-1);
//       }
//    }
//    pthread_exit(NULL);

  const int dim = 1024;

  const openvdb::Vec3f center(0.35f, 0.35f, 0.35f);
  const float radius = 0.15f, voxelSize = 1.0f / (dim - 1);
  const float halfWidth = 3.0f;

  typedef openvdb::FloatGrid GridT;
  typedef openvdb::tools::EnrightField<float> FieldT;
  typedef openvdb::tools::LevelSetAdvection<GridT, FieldT> AdvectT;

  GridT::Ptr grid = openvdb::tools::createLevelSetSphere<GridT>(
      radius, center, voxelSize, halfWidth);

  FieldT field;

  AdvectT advect(*grid, field);
  advect.setSpatialScheme(openvdb::math::HJWENO5_BIAS);
  advect.setTemporalScheme(openvdb::math::TVD_RK2);
  advect.setTrackerSpatialScheme(openvdb::math::HJWENO5_BIAS);
  advect.setTrackerTemporalScheme(openvdb::math::TVD_RK1);
  advect.setGrainSize(4);
  advect.setNormCount(3);
  double t = 0;
  int numCFL = advect.advect(t, t + 0.00001f);
  return 10;
}

EMSCRIPTEN_BINDINGS(viennatswasm) { emscripten::function("myrun", &myrun); }