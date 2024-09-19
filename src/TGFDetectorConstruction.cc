#include "TGFDetectorConstruction.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4Material.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RunManager.hh"
#include "G4AutoDelete.hh"
#include "G4SDManager.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4FieldManager.hh"

#include "TGFElectricFieldSetup.hh"

TGFDetectorConstruction::TGFDetectorConstruction()
{}

TGFDetectorConstruction::~TGFDetectorConstruction()
{}


G4VPhysicalVolume* TGFDetectorConstruction::Construct()
{
	
	// Material
	
	//G4double density_on_sea_level = 1.29e-3;  // 1.29
	//G4double density_on_TS = 0.81e-3;  // density calculated by Huseyin: 0.8315e-3, by Ilyas: 0.81e-3
	//G4double density_on_TS = 0.45e-3;  // density calculated by Huseyin: 0.4471e-3, by Ilyas: 0.81e-3 for 5 km up

	G4Material *WorldMat = new G4Material("WorldMat", 0.00000000000000025 * g/cm3, 3);     
	WorldMat->AddElement(nist->FindOrBuildElement("N"), 75.5 * perCent);
	WorldMat->AddElement(nist->FindOrBuildElement("O"), 23.2 * perCent);
	WorldMat->AddElement(nist->FindOrBuildElement("Ar"), 1.28 * perCent);

	// World
	G4Box *solidWorld = new G4Box("solidWorld", 2.5 * km, 2.5 * km, 2.5 * km);
	flogicWorld = new G4LogicalVolume(solidWorld, WorldMat, "flogicWorld");
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), flogicWorld, "physWorld", 0, false, 0, true);
	

	CreateAtmosphere();
	CreateCloud();

	return physWorld;
}


void TGFDetectorConstruction::CreateCloud()
{
	G4Material *cloud[n_layers_cloud];
	for (int i =0; i < n_layers_cloud; i++)
	{
		cloud[i]= new G4Material("cloud"+ std::to_string(i), (density_on_TS*exp(-(1000.+i*10.)/8400.)) * g/cm3, 3);
		cloud[i]->AddElement(nist->FindOrBuildElement("N"), 75.5 * perCent);
		cloud[i]->AddElement(nist->FindOrBuildElement("O"), 23.2 * perCent);
		cloud[i]->AddElement(nist->FindOrBuildElement("Ar"), 1.28 * perCent);
	}


	// Tube
	G4VPhysicalVolume * physCloud[n_layers_cloud];

	G4Tubs *solidCloud = new G4Tubs("solidCloud", 0.0*km, 0.75*km, 5.*m,0.0*deg, 360.0*deg);
	for (int i =0; i < n_layers_cloud; i++)
	{
		fLogicCloud[i] = new G4LogicalVolume(solidCloud, cloud[i], "fLogicCloud"+std::to_string(i));
		physCloud[i] = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), fLogicCloud[i], "physCloud"+ std::to_string(i), fLogicAtmosphere[100+i], false, 0, true);
	}
}


void TGFDetectorConstruction::CreateAtmosphere()
{
	
	G4Material *Atmosphere[n_layers_atmosphere];
	for (int i =0; i < n_layers_atmosphere; i++)
	{
		Atmosphere[i]= new G4Material("Atmosphere"+ std::to_string(i), (density_on_TS*exp(-(i*10.)/8400.)) * g/cm3, 3);
		Atmosphere[i]->AddElement(nist->FindOrBuildElement("N"), 75.5 * perCent);
		Atmosphere[i]->AddElement(nist->FindOrBuildElement("O"), 23.2 * perCent);
		Atmosphere[i]->AddElement(nist->FindOrBuildElement("Ar"), 1.28 * perCent);
	}

	G4VPhysicalVolume * physAtmosphere[n_layers_atmosphere];
	G4Box *solidAtmosphere = new G4Box("solidAtmosphere", 2.5 * km, 2.5 * km, 5. * m);
	for (int i =0; i< n_layers_atmosphere; i++)
	{
		fLogicAtmosphere[i] = new G4LogicalVolume(solidAtmosphere, Atmosphere[i], "fLogicAtmosphere"+std::to_string(i)); 
		G4double z_coord = (-2495. + i*10.0)*m;
		physAtmosphere[i] = new G4PVPlacement(0, G4ThreeVector(0., 0., z_coord), fLogicAtmosphere[i], "physAtmosphere"+ std::to_string(i), flogicWorld, false, 0, true);
	}
}




void TGFDetectorConstruction::SetFieldVector(G4ThreeVector fieldVector)
{
	fFieldVector = fieldVector;
	G4cout << G4endl << "fFieldVector was set to " << fFieldVector << G4endl << G4endl;
}

void TGFDetectorConstruction::ConstructSDandField()
{
/*	
	TGFElectricFieldSetup *localElectricField = new TGFElectricFieldSetup();

	G4FieldManager *localFieldManager = new G4FieldManager();

	//localFieldManager->SetDetectorField(localElectricField);
	localFieldManager->SetDetectorField(localElectricField->GetField());

	//flogicWorld->SetFieldManager(localElectricField.Get()->GetLocalFieldManager(), allLocal );
	flogicWorld->SetFieldManager(localFieldManager, true);
*/

	
	TGFElectricFieldSetup* fieldSetup = new TGFElectricFieldSetup(fFieldVector);
	for (int i =0; i < 300; i++)
	{
		fLogicCloud[i]->SetFieldManager(fieldSetup->GetLocalFieldManager(), true);
	}
}





