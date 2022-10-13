# Compile time test, no need to exec
test_main = static_library('test_main', sources: ['catch_main.cpp'], dependencies: [catch2])

eenum_test = executable(
	'eenum',
	'eenum.cpp',
	link_with: [test_main],
	dependencies: [eenum, catch2]
)


test('eenum test', eenum_test)