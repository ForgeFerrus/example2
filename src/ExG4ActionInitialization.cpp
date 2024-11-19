
#include "ExG4ActionInitialization.hh"
#include "ExG4PrimaryGeneratorAction.hh"

ExG4ActionInitialization::ExG4ActionInitialization()
    : G4VUserActionInitialization()
{}
ExG4ActionInitialization::~ExG4ActionInitialization()
{}
    void ExG4ActionInitialization::Build() const
{
SetUserAction(new ExG4PrimaryGeneratorAction);
}