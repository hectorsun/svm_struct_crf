cmake_minimum_required(VERSION 2.8)
project( SvmSturct)
find_package( OpenCV REQUIRED )
find_package(Boost REQUIRED COMPONENTS serialization)

include_directories( ${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} .)

# qpbo lib
add_library(qpbo SHARED qpbo/QPBO.cpp qpbo/QPBO_extra.cpp qpbo/QPBO_maxflow.cpp qpbo/QPBO_postprocessing.cpp)

# svm_light lib
add_library(svm_light SHARED  svm_light/svm_hideo.c  svm_light/svm_common.c  svm_light/svm_learn.c )
target_link_libraries(svm_light m)

# svm_struct lib
add_library(svm_struct SHARED svm_struct_api.cpp svm_struct_learn_custom.cpp  svm_struct/svm_struct_learn.cpp svm_struct/svm_struct_common.cpp)
target_link_libraries(svm_struct svm_light qpbo ${Boost_LIBRARIES} ${OpenCV_LIBS} m)


# execuate file
add_executable(svm_crf_classify  svm_struct/svm_struct_classify.cpp)
target_link_libraries(svm_crf_classify svm_light svm_struct ${Boost_LIBRARIES})

add_executable(svm_crf_learn  svm_struct/svm_struct_main.cpp)
target_link_libraries(svm_crf_learn svm_light svm_struct ${Boost_LIBRARIES})


add_subdirectory(test)
