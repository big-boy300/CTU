package service;

import dao.DAOLayer;
import tables.PaymentcontrolEntity;
import tables.PaymentcontrolEntityPK;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.EntityTransaction;
import javax.persistence.Persistence;
import java.util.HashMap;

public class PaymentControlOperations implements DAOLayer {
    private final EntityManagerFactory emf = Persistence.createEntityManagerFactory("default");
    private final EntityManager manager = emf.createEntityManager();
    private final EntityTransaction transaction = manager.getTransaction();

    PaymentcontrolEntity paymentControl = new PaymentcontrolEntity();
    PaymentcontrolEntityPK paymentcontrolEntityPK = new PaymentcontrolEntityPK();

    @Override
    public void findData(HashMap<String, String> pks) {
        String employeeId = pks.get("employeeID");
        String paymentNum = pks.get("payment");

        paymentcontrolEntityPK.setEmployeeid(employeeId);
        paymentcontrolEntityPK.setPayment(paymentNum);

        paymentControl = manager.find(PaymentcontrolEntity.class, paymentcontrolEntityPK);
        System.out.println(paymentControl);
    }

    @Override
    public void addData(HashMap<String, String> data) {

        transaction.begin();

        String employeeId = data.get("employeeID");
        String paymentNum = data.get("payment");
        String studentId = data.get("studentID");

        paymentControl.setEmployeeid(employeeId);
        paymentControl.setPayment(paymentNum);
        paymentControl.setStudentid(studentId);

        manager.persist(paymentControl);

        transaction.commit();

    }

    @Override
    public void removeData(HashMap<String, String> pks) {
        transaction.begin();

        String employeeId = pks.get("employeeID");
        String paymentNum = pks.get("payment");

        paymentcontrolEntityPK.setEmployeeid(employeeId);
        paymentcontrolEntityPK.setPayment(paymentNum);

        paymentControl = manager.find(PaymentcontrolEntity.class, paymentcontrolEntityPK);

        manager.remove(paymentControl);

        transaction.commit();

    }

    @Override
    public void updateData(HashMap<String, String> pks, HashMap<String, String> data) {
        transaction.begin();

        String employeeId = pks.get("employeeID");
        String paymentNum = pks.get("payment");

        paymentcontrolEntityPK.setEmployeeid(employeeId);
        paymentcontrolEntityPK.setPayment(paymentNum);

        paymentControl = manager.find(PaymentcontrolEntity.class, paymentcontrolEntityPK);

        if(data.containsKey("studentID")){
            String newStudentId = data.get("studentID");
            paymentControl.setStudentid(newStudentId);
        }

        manager.merge(paymentControl);

        transaction.commit();
    }
}
