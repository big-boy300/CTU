package datamanipulationapi;

import service.LessonOperations;

import java.util.HashMap;

public class LessonDataAPI {
    private LessonOperations lessonOperations = new LessonOperations();

    public void findLesson(String studentId, String teacherId, String level, String lang){
        HashMap<String, String> lessonToFind = new HashMap<>();

        lessonToFind.put("teacherID", teacherId);
        lessonToFind.put("studentID", studentId);
        lessonToFind.put("level", level);
        lessonToFind.put("lang", lang);

        lessonOperations.findData(lessonToFind);
    }

    public void addNewLesson(String studentId, String teacherId, String level, String lang){
        HashMap<String, String> newLesson = new HashMap<>();

        newLesson.put("teacherID", teacherId);
        newLesson.put("studentID", studentId);
        newLesson.put("level", level);
        newLesson.put("lang", lang);

        lessonOperations.addData(newLesson);
    }

    public void deleteLesson(String studentId, String teacherId, String level, String lang){
        HashMap<String, String> lessonToRemove = new HashMap<>();

        lessonToRemove.put("teacherID", teacherId);
        lessonToRemove.put("studentID", studentId);
        lessonToRemove.put("level", level);
        lessonToRemove.put("lang", lang);

        lessonOperations.removeData(lessonToRemove);
    }

    //transaction from CP4
    public void conductLessonSubstitution(String studentId, String teacherId, String level,
                                          String lang, String newTeacherId){
        HashMap<String, String> currentLesson = new HashMap<>();
        HashMap<String, String> lessonSubstData = new HashMap<>();


        currentLesson.put("studentID", studentId);
        currentLesson.put("teacherID", teacherId);
        currentLesson.put("level", level);
        currentLesson.put("lang", lang);

        if(newTeacherId != null && !newTeacherId.isEmpty()){
            lessonSubstData.put("teacherID", newTeacherId);
        }

        lessonOperations.lessonSubstitution(currentLesson, lessonSubstData);

    }
}
