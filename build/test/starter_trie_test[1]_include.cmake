if(EXISTS "/home/cky/Desktop/bust/build/test/starter_trie_test[1]_tests.cmake")
  include("/home/cky/Desktop/bust/build/test/starter_trie_test[1]_tests.cmake")
else()
  add_test(starter_trie_test_NOT_BUILT starter_trie_test_NOT_BUILT)
endif()
