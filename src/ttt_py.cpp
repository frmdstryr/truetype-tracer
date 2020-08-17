// experimental c++ port of truetype-tracer
// January 2012, anders.e.e.wallin "at" gmail.com
// Ported to use pybind frmdstryr at protonmail
#include <pybind11/pybind11.h>

namespace py = pybind11;
#include "ttt.hpp"
#include "writer.hpp"
#include "ngc_writer.hpp"
#include "dxf_writer.hpp"
#include "segment_writer.hpp"
//#include "segment_writer_py.hpp"
#include "version_string.hpp"

// this is the default font used if not specified on commandline
// #define TTFONT "/usr/share/fonts/truetype/freefont/FreeSerifBoldItalic.ttf"
#define TTFONT "/usr/share/fonts/truetype/freefont/FreeSerif.ttf"

std::string version() {
    return VERSION_STRING;
}

static std::string dxf1(std::string str) {
    Writer* wr = new DXF_Writer( );
    Ttt* ttt = new Ttt(wr, str, false, TTFONT);
    std::string outp = ttt->get_output();
    delete ttt;
    delete wr;
    return outp;
}

static std::string ngc1(std::string str) {
    Writer* wr = new NGC_Writer(  false, 0.003, false );
    wr->set_text(str);
    wr->set_font(TTFONT);
    Ttt* ttt = new Ttt(wr, str, false, TTFONT);
    std::string outp = ttt->get_output();
    delete ttt;
    delete wr;
    return outp;
}

static std::string dxf0() {
    return dxf1("Hello World.");
}

static std::string ngc0() {
    return ngc1("Hello World.");
}

static std::string ttt_with_writer(std::string str, Writer* wr) {
    //Writer* wr = new NGC_Writer( TTFONT, str, false, 0.003, false );
    if (str == "")
        str = "Hello world.";
    wr->set_text(str);
    //wr->set_font(TTFONT);
    Ttt* ttt = new Ttt(wr, str, false, wr->get_font() );
    std::string outp = ttt->get_output();
    delete ttt;
    //delete wr;
    return outp;
}

PYBIND11_MODULE(truetypetracer, m) {

    m.def("version", version);
    m.def("ngc", ngc0); // zero arguments. "hello world" with all else defaults
    m.def("ngc", ngc1);

    m.def("dxf", dxf1);
    m.def("dxf", dxf0);

    m.def("ttt", ttt_with_writer);
    py::class_<extents>(m, "extents")
        .def(py::init<>())
        .def_readwrite("minx", &extents::minx)
        .def_readwrite("miny", &extents::miny)
        .def_readwrite("maxy", &extents::maxy)
        .def_readwrite("maxx", &extents::maxx)
    ;
    py::class_<Writer>(m, "Writer") // No init since it has pure virtual fnctions
        .def_property("arc", &Writer::get_arc, &Writer::set_arc)
        .def_property("conic", &Writer::get_conic, &Writer::set_conic)
        .def_property("cubic", &Writer::get_cubic, &Writer::set_cubic)
        .def_property("scale", &Writer::get_scale, &Writer::set_scale)
        .def_property("conic_biarc_subdivision", &Writer::get_conic_biarc_subdiv, &Writer::set_conic_biarc_subdiv)
        .def_property("conic_line_subdivision", &Writer::get_conic_line_subdiv, &Writer::set_conic_line_subdiv)
        .def_property("cubic_biarc_subdivision", &Writer::get_cubic_biarc_subdiv, &Writer::set_cubic_biarc_subdiv)
        .def_property("cubic_line_subdivision", &Writer::get_cubic_line_subdiv, &Writer::set_cubic_line_subdiv)
        .def_property("extents", &Writer::get_extents, &Writer::set_extents)
        .def("set_font", &Writer::set_font_number)
        .def("set_font_by_path", &Writer::set_font_path)
    ;
    py::class_<NGC_Writer, Writer>(m, "NGC_Writer")
        .def(py::init<>())
        .def_property("blockdelete", &NGC_Writer::get_blockdelete, &NGC_Writer::set_blockdelete)
    ;
    py::class_<SEG_Writer, Writer>(m, "SEG_Writer")
        .def(py::init<>())
        .def("get_loops", &SEG_Writer::get_loops)
        .def("get_segments", &SEG_Writer::get_loops) // for backwards compatibility. remove at some point!
     ;

}
