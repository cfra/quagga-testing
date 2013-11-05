from testutils import expect

def run_test():
    program = expect.spawn("./testcases/lib/test_srcdest_table")
    yield program.expect('PRNG Test successful.\r\n', 'PRNG Test', timeout=20)
    yield program.finish()
