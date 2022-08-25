package service;

import dao.DAOLayer;
import tables.LessonEntity;
import tables.LessonEntityPK;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.EntityTransaction;
import javax.persistence.Persistence;
import java.util.HashMap;

public class LessonOperations implements DAOLayer {

    private final EntityManagerFactory emf = Persistence.createEntityManagerFactory("default");
    private final EntityManager manager = emf.createEntityManager();
    private final EntityTransaction transaction = manager.getTransaction();

    LessonEntity lesson = new LessonEntity();
    LessonEntityPK lessonEntityPK = new LessonEntityPK();

    @Override
    public void findData(HashMap<String, String> pks) {
        String studentId = pks.get("studentID");
        String teacherId = pks.get("teacherID");
        String level = pks.get("level");
        String lang = pks.get("lang");

        lessonEntityPK.setStudentid(studentId);
        lessonEntityPK.setTeacherid(teacherId);
        lessonEntityPK.setLevel(level);
        lessonEntityPK.setLanguage(lang);

        lesson = manager.find(LessonEntity.class, lessonEntityPK);
        System.out.println(lesson);

    }

    @Override
    public void addData(HashMap<String, String> data) {
        transaction.begin();

        String studentId = data.get("studentID");
        String teacherId = data.get("teacherID");
        String level = data.get("level");
        String lang = data.get("lang");

        lesson.setStudentid(studentId);
        lesson.setTeacherid(teacherId);
        lesson.setLevel(level);
        lesson.setLanguage(lang);

        manager.persist(lesson);

        transaction.commit();
    }

    @Override
    public void removeData(HashMap<String, String> pks) {
        String studentId = pks.get("studentID");
        String teacherId = pks.get("teacherID");
        String level = pks.get("level");
        String lang = pks.get("lang");

        lessonEntityPK.setStudentid(studentId);
        lessonEntityPK.setTeacherid(teacherId);
        lessonEntityPK.setLevel(level);
        lessonEntityPK.setLanguage(lang);

        lesson = manager.find(LessonEntity.class, lessonEntityPK);

        transaction.begin();

        manager.remove(lesson);

        transaction.commit();
    }

    @Override
    public void updateData(HashMap<String, String> pks, HashMap<String, String> data) {}

    //transaction from CP4
    public void lessonSubstitution(HashMap<String, String> curData, HashMap<String, String> newData){
        transaction.begin();

        String studentId = curData.get("studentID");
        String teacherId = curData.get("teacherID");
        String level = curData.get("level");
        String lang = curData.get("lang");

        lessonEntityPK.setStudentid(studentId);
        lessonEntityPK.setTeacherid(teacherId);
        lessonEntityPK.setLevel(level);
        lessonEntityPK.setLanguage(lang);

        lesson = manager.find(LessonEntity.class, lessonEntityPK);

        LessonEntityPK newLessonPK = new LessonEntityPK();
        LessonEntity newLesson = new LessonEntity();

        if(newData.containsKey("teacherID")){
            String newTeacherID = newData.get("teacherID");
            if(newTeacherID != null && !newTeacherID.isEmpty() && !newTeacherID.equals(teacherId)){
                manager.remove(lesson);
                newLesson.setStudentid(studentId);
                newLesson.setTeacherid(newTeacherID);
                newLesson.setLevel(level);
                newLesson.setLanguage(lang);
                manager.persist(newLesson);
            } else {
                System.out.println("New Teacher ID is either null or equals to the current teacher ID!");
                return;
            }
        }

        transaction.commit();
    }

}
