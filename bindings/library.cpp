#include <optional>
#include <pybind11/pybind11.h>

#include "branch_and_reduce/b_and_r.h"
#include "data_structure/graph_access.h"
#include "io/graph_io.h"
#include "partition/partition_config.h"
#include "redu_vcc/redu_vcc.h"
#include "redu_vcc/reducer.h"

namespace py = pybind11;

PYBIND11_MODULE(vcc, m) {
  py::class_<redu_vcc>(m, "redu_cc")
      .def(py::init<>())
      .def(py::init<graph_access &>(), py::arg("G"))
      .def(py::init<graph_access &, PartitionConfig &>(), py::arg("G"),
           py::arg("partition_config"))
      // Fairly unsafe public accessors. Making as read only for now
      .def_readonly("self_to_parent", &redu_vcc::num_nodes)
      .def_readonly("adj_list", &redu_vcc::adj_list)
      .def_readonly("node_status", &redu_vcc::node_status)
      .def_readonly("fold_node", &redu_vcc::fold_node)
      .def_readonly("merge_node", &redu_vcc::merge_node)
      .def_readonly("remaining_nodes", &redu_vcc::remaining_nodes)
      .def_readonly("clique_cover", &redu_vcc::clique_cover)
      .def_readonly("next_cliqueID", &redu_vcc::next_cliqueID)
      .def_readonly("next_solvecliqueID", &redu_vcc::next_solvecliqueID)
      .def_readonly("node_clique", &redu_vcc::node_clique)
      .def_readonly("solve_node_clique", &redu_vcc::solve_node_clique)
      .def_readonly("node_mis", &redu_vcc::node_mis)
      .def_readonly("curr_mis", &redu_vcc::curr_mis)
      .def_readonly("kernel_adj_list", &redu_vcc::kernel_adj_list)
      .def_readonly("kernel_edges", &redu_vcc::kernel_edges)
      .def_readonly("scratch1", &redu_vcc::scratch1)
      .def_readonly("scratch2", &redu_vcc::scratch2)
      // Binding methods
      .def("removeVertex", &redu_vcc::removeVertex, py::arg("v"))
      .def("addVertex", &redu_vcc::addVertex, py::arg("v"))
      .def("removeVertexSet", &redu_vcc::removeVertexSet, py::arg("S"))
      .def("addVertexSet", &redu_vcc::addVertexSet, py::arg("S"))
      .def("adj_size", &redu_vcc::adj_size, py::arg("v"))
      .def("curr_adj_list", &redu_vcc::curr_adj_list, py::arg("v"))
      //      .def("printAdjList", &redu_vcc::printAdjList) dont bind this
      //      overload as we don't have std::nullopt in c++ 14
//      .def("printAdjList", py::overload_cast<NodeID>(&redu_vcc::printAdjList), py::arg("v"))
      .def("printNeighborhood", &redu_vcc::printNeighborhood, py::arg("v"))
      .def("printVectorSet", &redu_vcc::printVectorSet, py::arg("S"))
      .def("addCliquesToParent", &redu_vcc::addCliquesToParent, py::arg("parent"))
      .def("addClique", &redu_vcc::addClique, py::arg("clique"))
      .def("addCliqueToCover", &redu_vcc::addCliqueToCover, py::arg("clique"))
      .def("pop_clique", &redu_vcc::pop_clique, py::arg("clique"))
      .def("getCliqueID", &redu_vcc::getCliqueID, py::arg("v"))
      .def("getClique", &redu_vcc::getClique, py::arg("v"))
      .def("replaceClique", &redu_vcc::replaceClique, py::arg("cliqueID"), py::arg("new_clique"))
      .def("build_cover", &redu_vcc::build_cover)
      .def("validateCover", &redu_vcc::validateCover, py::arg("G"))
      ;

  py::class_<graph_access>(m, "graph_access")
      .def(py::init<>())
      .def("start_construction", &graph_access::start_construction,
           py::arg("nodes"), py::arg("edges"))
      .def("new_node", &graph_access::new_node)
      .def("new_edge", &graph_access::new_edge, py::arg("source"),
           py::arg("target"))
      .def("finish_construction", &graph_access::finish_construction)
      .def("number_of_nodes", &graph_access::number_of_nodes)
      .def("number_of_edges", &graph_access::number_of_edges)
      .def("get_first_edge", &graph_access::get_first_edge, py::arg("node"))
      .def("get_first_invalid_edge", &graph_access::get_first_invalid_edge,
           py::arg("node"))
      .def("get_first_invalid_edge", &graph_access::get_partition_count)
      .def("set_partition_count", &graph_access::set_partition_count,
           py::arg("count"))
      .def("getSeparatorBlock", &graph_access::getSeparatorBlock)
      .def("setSeparatorBlock", &graph_access::setSeparatorBlock, py::arg("id"))
      .def("getPartitionIndex", &graph_access::getPartitionIndex,
           py::arg("node"))
      .def("setPartitionIndex", &graph_access::setPartitionIndex,
           py::arg("node"), py::arg("id"))
      .def("getSecondPartitionIndex", &graph_access::getSecondPartitionIndex,
           py::arg("node"))
      .def("setSecondPartitionIndex", &graph_access::setSecondPartitionIndex,
           py::arg("node"), py::arg("id"))
      .def("resizeSecondPartitionIndex",
           &graph_access::resizeSecondPartitionIndex, py::arg("no_nodes"))
      .def("getNodeWeight", &graph_access::getNodeWeight, py::arg("node"))
      .def("setNodeWeight", &graph_access::setNodeWeight, py::arg("node"),
           py::arg("weight"))
      .def("getNodeDegree", &graph_access::getNodeDegree, py::arg("node"))
      .def("getWeightedNodeDegree", &graph_access::getWeightedNodeDegree,
           py::arg("node"))
      .def("getMaxDegree", &graph_access::getMaxDegree)
      .def("getEdgeWeight", &graph_access::getEdgeWeight, py::arg("edge"))
      .def("setEdgeWeight", &graph_access::setEdgeWeight, py::arg("edge"),
           py::arg("weight"))
      .def("getEdgeTarget", &graph_access::getEdgeTarget, py::arg("edge"))
      .def("getEdgeRating", &graph_access::getEdgeRating, py::arg("edge"))
      .def("setEdgeRating", &graph_access::setEdgeRating, py::arg("edge"),
           py::arg("rating"))
      .def("copy", &graph_access::copy, py::arg("Gcopy"))

      ;

  py::class_<graph_io>(m, "graph_io")
      .def(py::init<>())
      .def_static("readGraphWeighted", &graph_io::readGraphWeighted,
                  py::arg("G"), py::arg("filename"))
      .def_static("readGraphKernel", &graph_io::readGraphKernel, py::arg("G"),
                  py::arg("reduVCC"))
      .def_static("writeGraphWeighted", &graph_io::writeGraphWeighted,
                  py::arg("G"), py::arg("filename"))
      .def_static("writeGraph", &graph_io::writeGraph, py::arg("G"),
                  py::arg("filename"))
      .def_static("readPartition", &graph_io::readPartition, py::arg("G"),
                  py::arg("filename"))
      .def_static("writePartition", &graph_io::writePartition, py::arg("G"),
                  py::arg("filename"));

  // TODO(Alexandre.Amice). Seems like NodeID, EdgeID, PartitionId, NodeWeight, cliqueID
  // may all be important
}