#!/usr/bin/env python3
import vcc
import unittest

class TestGraphAccess(unittest.TestCase):
    def test_graph_access(self):
        g = vcc.graph_access()
        # when you start construction you need to know the size of your graph. Otherwise you can segfault
        g.start_construction(2, 2)
        id1 = g.new_node()
        id2 = g.new_node()
        edge = g.new_edge(id1, id2)
#
class TestReduVcc(unittest.TestCase):
    def test_redu_vcc(self):
        r1 = vcc.redu_vcc()
        g = vcc.graph_access()
        # when you start construction you need to know the size of your graph. Otherwise you can segfault
        g.start_construction(2, 2)
        id1 = g.new_node()
        id2 = g.new_node()
        edge = g.new_edge(id1, id2)
        r = vcc.redu_vcc(g)


