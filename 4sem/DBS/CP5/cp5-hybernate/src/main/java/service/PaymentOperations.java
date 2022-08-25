package service;

import dao.DAOLayer;
import tables.PaymentEntity;
import tables.PaymentEntityPK;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.EntityTransaction;
import javax.persistence.Persistence;
import java.util.HashMap;

public class PaymentOperations implements DAOLayer {
    private final EntityManagerFactory emf = Persistence.createEntityManagerFactory("default");
    private final EntityManager manager = emf.createEntityManager();
    private final EntityTransaction transaction = manager.getTransaction();

    PaymentEntity payment = new PaymentEntity();
    PaymentEntityPK paymentEntityPK = new PaymentEntityPK();

    @Override
    public void findData(HashMap<String, String> pks) {
        String studentId = pks.get("studentID");
        String paymentNum = pks.get("number");

        paymentEntityPK.setStudentid(studentId);
        paymentEntityPK.setNumber(paymentNum);

        payment = manager.find(PaymentEntity.class, paymentEntityPK);
        System.out.println(payment);

    }

    @Override
    public void addData(HashMap<String, String> data) {
        transaction.begin();

        String studentId = data.get("studentID");
        String number = data.get("number");
        String method = data.get("method");

        payment.setStudentid(studentId);
        payment.setNumber(number);
        payment.setMethod(method);

        manager.persist(payment);

        transaction.commit();
    }

    @Override
    public void removeData(HashMap<String, String> pks) {
        transaction.begin();

        String studentId = pks.get("studentID");
        String paymentNum = pks.get("number");

        paymentEntityPK.setStudentid(studentId);
        paymentEntityPK.setNumber(paymentNum);

        payment = manager.find(PaymentEntity.class, paymentEntityPK);

        manager.remove(payment);

        transaction.commit();
    }

    @Override
    public void updateData(HashMap<String, String> pks, HashMap<String, String> newData) {
        transaction.begin();

        String studentId = pks.get("studentID");
        String paymentNum = pks.get("number");

        paymentEntityPK.setStudentid(studentId);
        paymentEntityPK.setNumber(paymentNum);

        payment = manager.find(PaymentEntity.class, paymentEntityPK);

        if(newData.containsKey("method")){
            String newMethod = newData.get("method");
            payment.setMethod(newMethod);
        }

        manager.merge(payment);

        transaction.commit();
    }
}
