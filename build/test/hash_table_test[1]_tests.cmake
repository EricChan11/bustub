add_test( HashTableTest.SampleTest /home/cky/Desktop/bust/build/test/hash_table_test [==[--gtest_filter=HashTableTest.DISABLED_SampleTest]==] --gtest_also_run_disabled_tests [==[--gtest_color=auto]==] [==[--gtest_output=xml:/home/cky/Desktop/bust/build/test/hash_table_test.xml]==] [==[--gtest_catch_exceptions=0]==])
set_tests_properties( HashTableTest.SampleTest PROPERTIES DISABLED TRUE)
set_tests_properties( HashTableTest.SampleTest PROPERTIES WORKING_DIRECTORY /home/cky/Desktop/bust/build/test TIMEOUT 120)
set( hash_table_test_TESTS HashTableTest.SampleTest)
