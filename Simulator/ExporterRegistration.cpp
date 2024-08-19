#include "SimulatorBase.h"
#include "Exporter/ExporterBase.h"
#include "Exporter/ParticleExporter_Partio.h"
#include "Exporter/ParticleExporter_VTK.h"
#include "Exporter/RigidBodyExporter_BIN.h"
#include "Exporter/RigidBodyExporter_OBJ.h"
#include "Exporter/RigidBodyExporter_PLY.h"
#include "Exporter/RigidBodyExporter_VTK.h"

using namespace SPH;

void SimulatorBase::createExporters()
{
	addParticleExporter("enablePartioExport", "Partio Exporter", "Enable/disable partio export.", std::make_shared<ParticleExporter_Partio>(this));
	addParticleExporter("enableVTKExport", "VTK Exporter", "Enable/disable VTK export.", std::make_shared<ParticleExporter_VTK>(this));

	addRigidBodyExporter("enableRigidBodyExport", "Rigid Body Exporter", "Enable/disable rigid body BIN export.", std::make_shared<RigidBodyExporter_BIN>(this));
	addRigidBodyExporter("enableRigidBodyOBJExport", "Rigid Body OBJ Exporter", "Enable/disable rigid body OBJ export.", std::make_shared<RigidBodyExporter_OBJ>(this));
	addRigidBodyExporter("enableRigidBodyPLYExport", "Rigid Body PLY Exporter", "Enable/disable rigid body PLY export.", std::make_shared<RigidBodyExporter_PLY>(this));
	addRigidBodyExporter("enableRigidBodyVTKExport", "Rigid Body VTK Exporter", "Enable/disable rigid body VTK export.", std::make_shared<RigidBodyExporter_VTK>(this));
}