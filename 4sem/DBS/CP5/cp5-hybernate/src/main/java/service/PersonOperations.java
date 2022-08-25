package service;

import dao.DAOLayer;
import tables.PersonEntity;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.EntityTransaction;
import javax.persistence.Persistence;
import java.util.HashMap;

public class PersonOperations implements DAOLayer {

    private final EntityManagerFactory emf = Persistence.createEntityManagerFactory("default");
    private final EntityManager manager = emf.createEntityManager();
    private final EntityTransaction transaction = manager.getTransaction();

    private PersonEntity person = new PersonEntity();

    @Override
    public void findData(HashMap<String, String> pks) {
        String langSchoolCardNumber = pks.get("langschoolcardnumber");
        person = manager.find(PersonEntity.class, langSchoolCardNumber);
        System.out.println(person);
    }

    @Override
    public void addData(HashMap<String, String> data) {
        transaction.begin();

        String passport = data.get("passport");
        String langSchoolCardNumber = data.get("langschoolcardnumber");
        String name = data.get("name");
        String street = data.get("street");
        String email = data.get("email");
        person.setPassport(passport);
        person.setLangschoolcardnumber(langSchoolCardNumber);
        person.setName(name);
        person.setStreet(street);
        person.setEmail(email);

        manager.persist(person);

        transaction.commit();
    }

    @Override
    public void removeData(HashMap<String, String> pks) {
        String langSchoolCardNumber = pks.get("langschoolcardnumber");

        transaction.begin();

        person = manager.find(PersonEntity.class, langSchoolCardNumber);
        manager.remove(person);

        transaction.commit();
    }

    @Override
    public void updateData(HashMap <String, String> pks, HashMap <String, String> data) {
        transaction.begin();

        String pk = pks.get("langschoolcardnumber");
        person = manager.find(PersonEntity.class, pk);

        if(data.containsKey("passport")){
            String passport = data.get("passport");
            person.setPassport(passport);
        }
        if(data.containsKey("langschoolcardnumber")){
            String langSchoolCardNum = data.get("langschoolcardnumber");
            person.setLangschoolcardnumber(langSchoolCardNum);
        }
        if(data.containsKey("name")){
            String name = data.get("name");
            person.setName(name);
        }
        if(data.containsKey("street")){
            String street = data.get("street");
            person.setStreet(street);
        }
        if(data.containsKey("email")){
            String email = data.get("email");
            person.setEmail(email);
        }

        manager.merge(person);

        transaction.commit();
    }

}
