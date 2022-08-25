package datamanipulationapi;

import service.PaymentControlOperations;

import java.util.HashMap;

public class PaymentControlDataAPI {
    private PaymentControlOperations paymentControlOperations = new PaymentControlOperations();

    public void findPaymentPaymentControl(String employeeId, String paymentNum){
        HashMap<String, String> paymentToFindData = new HashMap<>();

        paymentToFindData.put("employeeID", employeeId);
        paymentToFindData.put("payment", paymentNum);

        paymentControlOperations.findData(paymentToFindData);
    }

    public void addNewPaymentControl(String employeeId, String paymentNum, String studentId){
        HashMap<String, String> newPayment = new HashMap<>();

        newPayment.put("employeeID", employeeId);
        newPayment.put("payment", paymentNum);
        newPayment.put("studentID", studentId);

        paymentControlOperations.addData(newPayment);
    }

    public void deletePaymentControl(String employeeId, String paymentNum){
        HashMap<String, String> paymentToDelete = new HashMap<>();

        paymentToDelete.put("employeeID", employeeId);
        paymentToDelete.put("payment", paymentNum);

        paymentControlOperations.removeData(paymentToDelete);
    }

    public void updatePaymentControl(String employeeId, String paymentNum, String newStudentId){
        HashMap<String, String> pks = new HashMap<>();
        HashMap<String, String> updateData = new HashMap<>();

        pks.put("employeeID", employeeId);
        pks.put("payment", paymentNum);

        if(newStudentId != null && !newStudentId.isEmpty()){
            updateData.put("studentID", newStudentId);
        }

        paymentControlOperations.updateData(pks, updateData);
    }
}
