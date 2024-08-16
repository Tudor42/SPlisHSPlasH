//
// Created by sjeske on 1/22/20.
//
#include "common.h"

#include <SPlisHSPlasH/TimeManager.h>
#include <SPlisHSPlasH/TimeStep.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

void TimeModule(py::module m_sub) {
    // ---------------------------------------
    // Class Time Manager
    // ---------------------------------------
    py::class_<SPH::TimeManager, GenParam::ParameterObject>(m_sub, "TimeManager")
            .def_readwrite_static("TIME_STEP_SIZE", &SPH::TimeManager::TIME_STEP_SIZE)

            .def(py::init<>())
            .def_static("getCurrent", &SPH::TimeManager::getCurrent, py::return_value_policy::reference)
            .def_static("setCurrent", &SPH::TimeManager::setCurrent)
            .def_static("hasCurrent", &SPH::TimeManager::hasCurrent)

            .def("getTime", &SPH::TimeManager::getTime)
            .def("setTime", &SPH::TimeManager::setTime)
            .def("getTimeStepSize", &SPH::TimeManager::getTimeStepSize)
            .def("setTimeStepSize", &SPH::TimeManager::setTimeStepSize)

            .def("saveState", &SPH::TimeManager::saveState)
            .def("loadState", &SPH::TimeManager::loadState);

    // ---------------------------------------
    // Abstract Class Time Step
    // ---------------------------------------
    /*
    py::class_<SPH::TimeStep, GenParam::ParameterObject>(m_sub, "TimeStep")
            .def_readwrite_static("SOLVER_ITERATIONS", &SPH::TimeStep::SOLVER_ITERATIONS)
            .def_readwrite_static("MIN_ITERATIONS", &SPH::TimeStep::MIN_ITERATIONS)
            .def_readwrite_static("MAX_ITERATIONS", &SPH::TimeStep::MAX_ITERATIONS)
            .def_readwrite_static("MAX_ERROR", &SPH::TimeStep::MAX_ERROR)

            .def("step", &SPH::TimeStep::step)
            .def("reset", &SPH::TimeStep::reset)
            .def("init", &SPH::TimeStep::init)
            .def("resize", &SPH::TimeStep::resize)
            .def("emittedParticles", &SPH::TimeStep::emittedParticles)
            .def("saveState", &SPH::TimeStep::saveState)
            .def("loadState", &SPH::TimeStep::loadState);
    */
    class PyTimeStep : public SPH::TimeStep {
    protected:
        void initParameters() override {
            PYBIND11_OVERRIDE(void, SPH::TimeStep, initParameters, ); 
        }
    public:
        void step() override {
            PYBIND11_OVERRIDE_PURE(void, SPH::TimeStep, step, );
        }
        
        void reset() override {
            PYBIND11_OVERRIDE(void, SPH::TimeStep, reset, );
        }
        
        void init() override {
            PYBIND11_OVERRIDE(void, SPH::TimeStep, init, );
        }
        
        void resize() override {
            PYBIND11_OVERRIDE_PURE(void, SPH::TimeStep, resize, );
        }

        void emittedParticles(SPH::FluidModel *model, const unsigned int startIndex) override {
            PYBIND11_OVERRIDE(void, SPH::TimeStep, emittedParticles, model, startIndex);
        }

        void performNeighborhoodSearchSort() {
            PYBIND11_OVERRIDE(void, SPH::TimeStep, performNeighborhoodSearchSort, );
        }

        void saveState(SPH::BinaryFileWriter &binWriter) {
            PYBIND11_OVERRIDE(void, SPH::TimeStep, saveState, binWriter);
        }

        void loadState(SPH::BinaryFileReader &binReader) {
            PYBIND11_OVERRIDE(void, SPH::TimeStep, loadState, binReader);
        }
    };

    class PublicistTimeStep : public SPH::TimeStep { 
    public:
        using SPH::TimeStep::initParameters;
    };

    py::class_<SPH::TimeStep, PyTimeStep, std::shared_ptr<SPH::TimeStep>>(m_sub, "TimeStep")
        .def(py::init<>())
        .def("initParameters", &PublicistTimeStep::initParameters)
        .def("step", &SPH::TimeStep::step)
        .def("reset", &SPH::TimeStep::reset)
        .def("init", &SPH::TimeStep::init)
        .def("resize", &SPH::TimeStep::resize)
        .def("emittedParticles", &SPH::TimeStep::emittedParticles)
        .def("performNeighborhoodSearchSort", &SPH::TimeStep::performNeighborhoodSearchSort)
        .def("saveState", &SPH::TimeStep::saveState)
        .def("loadState", &SPH::TimeStep::loadState);
}