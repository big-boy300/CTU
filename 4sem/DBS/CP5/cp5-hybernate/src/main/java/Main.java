import datamanipulationapi.LessonDataAPI;
import datamanipulationapi.PaymentControlDataAPI;
import datamanipulationapi.PaymentDataAPI;
import datamanipulationapi.PersonDataAPI;

public class Main {
    public static void main(String[] args) {
//        personEntityOperations();

//        lessonEntityOperations();

//        paymentEntityOperations();

//        paymentControlEntityOperations();

    }

    public static void personEntityOperations(){
        PersonDataAPI personDataAPI = new PersonDataAPI();

        //find person by PK, which is Language School Card Number
        String personToFindPK = "14979929";
        personDataAPI.findPerson(personToFindPK);

        //add new person
        String passport = "123456789";
        String langSchoolCardNum = "12345678";
        String name = "Marcus Aurelius";
        String street = "Ancient Rome str";
        String email = "marcaur@ancient.com";
//        personDataAPI.addNewPerson(passport, langSchoolCardNum, name, street, email);

        //remove person
//        personDataAPI.removePerson(langSchoolCardNum);

        //update person data
        String personToUpdatePK = "28499744";
//        personDataAPI.updatePersonData(personToUpdatePK, null, null, "Bobby Black", null, null );

    }

    public static void lessonEntityOperations(){
        //find lesson
        LessonDataAPI lessonDataAPI = new LessonDataAPI();
        String studentID = "90996892";
        String teacherID = "28010606";
        String level = "A2";
        String language = "English";
//        lessonDataAPI.findLesson(studentID, teacherID, level, language);

        //add lesson
        String newStudentID = "61078773";
        String newTeacherID = "27587298";
        String newLevel = "B1";
        String newLanguage = "German";
//        lessonDataAPI.addNewLesson(newStudentID, newTeacherID, newLevel, newLanguage);

        //remove lesson
        String studentIDToRemove = "61078773";
        String teacherIDToRemove = "27587298";
        String levelToRemove = "B1";
        String languageToRemove = "German";
//        lessonDataAPI.deleteLesson(studentIDToRemove, teacherIDToRemove, levelToRemove, languageToRemove);

        //update is impossible because all the columns are primary keys

        //transaction from CP4
        String currentStudentId = "90996892";
        String currentTeacherId = "89284302";//"28010606";
        String currentLevel = "A2";
        String currentLanguage = "English";
        String newTeacherId = "28010606"; //"89284302";
//        lessonDataAPI.conductLessonSubstitution(currentStudentId, currentTeacherId, currentLevel,
//                currentLanguage, newTeacherId);

    }

    public static void paymentEntityOperations(){
        PaymentDataAPI paymentDataAPI = new PaymentDataAPI();

        //find payment
        String studentId = "90996892";
        String number = "190625157952405";
//        paymentDataAPI.findPayment(studentId, number);

        //add new payment
        String newPaymentStudentId = "61078773";
        String newPaymentNumber = "123456789101213";
        String newPaymentMethod = "cash";
//        paymentDataAPI.addNewPayment(newPaymentStudentId, newPaymentNumber, newPaymentMethod);

        //delete paymnet
        String paymentToDeleteStudentId = "61078773";
        String paymentToDeleteNumber = "123456789101213";
//        paymentDataAPI.deletePayment(paymentToDeleteStudentId, paymentToDeleteNumber);

        //update payment data
        String paymentToUpdateStudentId = "61078773";
        String paymentToUpdateNumber = "123456789101213";
        String paymentToUpdateNewMethod = "online";
//        paymentDataAPI.updatePaymentInfo(paymentToUpdateStudentId, paymentToUpdateNumber, paymentToUpdateNewMethod);
    }

    public static void paymentControlEntityOperations(){
        PaymentControlDataAPI paymentControlDataAPI = new PaymentControlDataAPI();
        String employeeId = "25171642";
        String paymentNum = "190625157952405";
//        paymentControlDataAPI.findPayment(employeeId, paymentNum);

        String newEmployeeId = "25171642";
        String newPaymentNum = "123456789101213";
        String newStudentId = "61078773";
//        paymentControlDataAPI.addNewPaymentControl(newEmployeeId, newPaymentNum, newStudentId);

        //delete payment control
        String paymentControlEmployeeId = "25171642";
        String paymentControlPaymentNumber = "123456789101213";
//        paymentControlDataAPI.deletePaymentControl(paymentControlEmployeeId, paymentControlPaymentNumber);

    }
}
