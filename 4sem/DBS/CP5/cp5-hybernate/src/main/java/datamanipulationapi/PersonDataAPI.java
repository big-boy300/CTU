package datamanipulationapi;

import service.PersonOperations;

import java.util.HashMap;

public class PersonDataAPI {
    private PersonOperations personOperations = new PersonOperations();

    public void findPerson(String personPk){
        HashMap<String, String> personToFindData = new HashMap<>();

        personToFindData.put("langschoolcardnumber", personPk);
        personOperations.findData(personToFindData);
    }

    public void addNewPerson(String passport, String langschoolcardnumber,
                             String name, String street, String email) {
        HashMap<String, String> newPersonData = new HashMap<>();

        newPersonData.put("passport", passport);
        newPersonData.put("langschoolcardnumber", langschoolcardnumber);
        newPersonData.put("name", name);
        newPersonData.put("street", street);
        newPersonData.put("email", email);
        personOperations.addData(newPersonData);
    }

    public void removePerson(String personPK){
        HashMap<String, String> personToRemoveData = new HashMap<>();

        personToRemoveData.put("langschoolcardnumber", personPK);
        personOperations.removeData(personToRemoveData);

    }

    public void updatePersonData(String personPK, String passport, String langschoolcardnumber,
                                 String name, String street, String email) {

        HashMap<String, String> pk = new HashMap<>();
        HashMap<String, String> personToUpdateData = new HashMap<>();

        pk.put("langschoolcardnumber", personPK);

        if(passport != null && !passport.isEmpty()){
            personToUpdateData.put("passport", passport);
        }

        if(langschoolcardnumber != null && !langschoolcardnumber.isEmpty()){
            personToUpdateData.put("langschoolcardnumber", langschoolcardnumber);
        }

        if(name != null && !name.isEmpty()){
            personToUpdateData.put("name", name);
        }

        if(street != null && !street.isEmpty()){
            personToUpdateData.put("street", street);
        }

        if(email != null && !email.isEmpty()){
            personToUpdateData.put("email", email);
        }

        personOperations.updateData(pk, personToUpdateData);

    }
}
