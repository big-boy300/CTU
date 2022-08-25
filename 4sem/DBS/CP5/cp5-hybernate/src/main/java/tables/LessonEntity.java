package tables;

import javax.persistence.*;

@Entity
@Table(name = "lesson", schema = "public", catalog = "danilrom")
@IdClass(LessonEntityPK.class)
public class LessonEntity {
    @Id
    @Column(name = "studentid")
    private String studentid;
    @Id
    @Column(name = "teacherid")
    private String teacherid;
    @Id
    @Column(name = "level")
    private String level;
    @Id
    @Column(name = "language")
    private String language;
    @ManyToOne
    @JoinColumn(name = "studentid", referencedColumnName = "langschoolcardnumber", nullable = false, insertable = false, updatable = false)
    private PersonEntity personByStudentid;
    @ManyToOne
    @JoinColumn(name = "studentid", referencedColumnName = "langschoolcardnumber", nullable = false, insertable = false, updatable = false)
    private StudentEntity studentByStudentid;
    @ManyToOne
    @JoinColumns({@JoinColumn(name = "teacherid", referencedColumnName = "teacherid", nullable = false, insertable = false, updatable = false), @JoinColumn(name = "level", referencedColumnName = "level", nullable = false, insertable = false, updatable = false), @JoinColumn(name = "language", referencedColumnName = "language", nullable = false, insertable = false, updatable = false)})
    private StudygroupEntity studygroupByFkLessonTeacherid;
    @ManyToOne
    @JoinColumns({@JoinColumn(name = "teacherid", referencedColumnName = "teacherid", nullable = false, insertable = false, updatable = false), @JoinColumn(name = "level", referencedColumnName = "level", nullable = false, insertable = false, updatable = false), @JoinColumn(name = "language", referencedColumnName = "language", nullable = false, insertable = false, updatable = false)})
    private StudygroupEntity studygroupByLessonFkTeacherLevelLang;

    public String getStudentid() {
        return studentid;
    }

    public void setStudentid(String studentid) {
        this.studentid = studentid;
    }

    public void setTeacherid(String teacherid) {
        this.teacherid = teacherid;
    }

    public void setLevel(String level) {
        this.level = level;
    }

    public void setLanguage(String language) {
        this.language = language;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        LessonEntity that = (LessonEntity) o;

        if (studentid != null ? !studentid.equals(that.studentid) : that.studentid != null) return false;
        if (teacherid != null ? !teacherid.equals(that.teacherid) : that.teacherid != null) return false;
        if (level != null ? !level.equals(that.level) : that.level != null) return false;
        if (language != null ? !language.equals(that.language) : that.language != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = studentid != null ? studentid.hashCode() : 0;
        result = 31 * result + (teacherid != null ? teacherid.hashCode() : 0);
        result = 31 * result + (level != null ? level.hashCode() : 0);
        result = 31 * result + (language != null ? language.hashCode() : 0);
        return result;
    }


    @Override
    public String toString() {
        return "LessonEntity{" +
                "studentid='" + studentid + '\'' +
                ", teacherid='" + teacherid + '\'' +
                ", level='" + level + '\'' +
                ", language='" + language + '\'' +
                '}';
    }
}
