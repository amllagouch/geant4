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

  // Define the World Material
  G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);
  G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
  G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);

  // Define Water material
  G4Element* elH  = new G4Element("Hydrogen","H" ,  1., 1.01*g/mole);
  G4Element* elO  = new G4Element("Oxygen", "O" ,  8., 16.00*g/mole);
  G4Material* H2O = new G4Material("Water",1.000*g/cm3, 2);

  H2O->AddElement(elH, 2);
  H2O->AddElement(elO, 1);

  G4cout << "H2O is " << H2O << G4endl;

  // Define the WaterBox
  G4Box *solidWaterBox = new G4Box("waterBox", 0.4*m, 0.4*m, 0.1*m);
  G4LogicalVolume *logicWaterBox = new G4LogicalVolume(solidWaterBox, H2O, "logicWaterBox");

  fScoringVolume = logicWaterBox;
  G4VPhysicalVolume * physWaterBox = new G4PVPlacement(0,
                                                       G4ThreeVector(0., 0., 0.2*m),
                                                       logicWaterBox,
                                                       "physWaterBox",
                                                       logicWorld, false, 0, true);

  // Array of sensitive detectors
  G4Box *solidDetector = new G4Box("solidDetector", // name
                                   0.005*m, // width
                                   0.005*m, // length
                                   0.01*m); // height

  logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");

  for(G4int i = 0;i<100; i++){
    for(G4int j=0;j<100;j++){
      G4VPhysicalVolume *physDetector = new G4PVPlacement(0,  // rotation
                                                          G4ThreeVector(-0.5*m+(i+0.5)*m/100, -0.5*m+(j+0.5)*m/100, 0.29*m),  // position
                                                          logicDetector,
                                                          "physDetector",
                                                          logicWorld,
                                                          false,
                                                          i+j*100,
                                                          true);
    }
  }
  return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
  MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
  logicDetector->SetSensitiveDetector(sensDet);
}
