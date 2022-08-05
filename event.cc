#include "event.hh"
#include "G4UnitsTable.hh"

MyEventAction::MyEventAction(MyRunAction*)
{
  fEnergyDeposit=0.;
}

MyEventAction::~MyEventAction(){}


void MyEventAction::BeginOfEventAction(const G4Event*)
{
  fEnergyDeposit = 0.;
}

void MyEventAction::EndOfEventAction(const G4Event*)
{
  G4cout << "Energy Deposition: "  << G4BestUnit(fEnergyDeposit, "Energy") << G4endl;

  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->FillNtupleDColumn(1, 0, fEnergyDeposit);
  man->AddNtupleRow(1);
}
