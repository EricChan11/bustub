if(EXISTS "/home/cky/Desktop/bust/build/test/b_plus_tree_insert_test[1]_tests.cmake")
  include("/home/cky/Desktop/bust/build/test/b_plus_tree_insert_test[1]_tests.cmake")
else()
  add_test(b_plus_tree_insert_test_NOT_BUILT b_plus_tree_insert_test_NOT_BUILT)
endif()
