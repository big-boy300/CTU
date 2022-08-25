package datamanipulationapi;

import service.PaymentOperations;

import java.util.HashMap;

public class PaymentDataAPI {

    private PaymentOperations paymentOperations = new PaymentOperations();

    public void findPayment(String studentId, String number){
        HashMap<String, String> paymentToFind = new HashMap<>();

        paymentToFind.put("studentID", studentId);
        paymentToFind.put("number", number);

        paymentOperations.findData(paymentToFind);
    }

    public void addNewPayment(String studentId, String number, String method){
        HashMap<String, String> newPayment = new HashMap<>();

        newPayment.put("studentID", studentId);
        newPayment.put("number", number);
        newPayment.put("method", method);

        paymentOperations.addData(newPayment);
    }

    public void deletePayment(String studentId, String number){
        HashMap<String, String> paymentToRemove = new HashMap<>();

        paymentToRemove.put("studentID", studentId);
        paymentToRemove.put("number", number);

        paymentOperations.removeData(paymentToRemove);
    }

    public void updatePaymentInfo(String studentId, String paymentNum, String newPaymentMethod){
        HashMap<String, String> currentPayment = new HashMap<>();
        HashMap<String, String> updatePaymentData = new HashMap<>();


        currentPayment.put("studentID", studentId);
        currentPayment.put("number", paymentNum);

        if(newPaymentMethod != null && !newPaymentMethod.isEmpty()){
            updatePaymentData.put("method", newPaymentMethod);
        }

        paymentOperations.updateData(currentPayment, updatePaymentData);

    }
}
