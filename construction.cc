#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction(){}
MyDetectorConstruction::~MyDetectorConstruction(){}

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
  G4NistManager *nist = G4NistManager::Instance();



  // G4Material *H2O = new G4Material("H2O", 1.000*g/cm3, 2);
  // H2O->AddElement(nist->FindOrBuildElement("H"), 2);
  // H2O->AddElement(nist->FindOrBuildElement("O"), 1);
  // G4Material* lAr = new G4Material("liquidArgon", 18., 39.95*g/mole,1.390*g/cm3);

  // define the World Material
  G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);
  G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
  G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);

  G4Element* elH  = new G4Element("Hydrogen","H" ,  1., 1.01*g/mole);
  G4Element* elO  = new G4Element("Oxygen", "O" ,  8., 16.00*g/mole);
  G4Material* H2O = new G4Material("Water",1.000*g/cm3,2);

  H2O->AddElement(elH, 2);
  H2O->AddElement(elO, 1);

  G4cout << "H2O is " << H2O << G4endl; 

  G4Box *solidWaterBox = new G4Box("waterBox", 0.4*m, 0.4*m, 0.1*m);
  G4LogicalVolume *logicWaterBox = new G4LogicalVolume(solidWaterBox, H2O, "logicWaterBox");
  G4VPhysicalVolume * physWaterBox = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.2*m), logicWaterBox, "physWaterBox", logicWorld, false, 0, true);
  return physWorld;
}
