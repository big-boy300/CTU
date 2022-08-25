package tables;

import javax.persistence.*;
import java.util.Collection;

@Entity
@Table(name = "studygroup", schema = "public", catalog = "danilrom")
@IdClass(StudygroupEntityPK.class)
public class StudygroupEntity {
    @Id
    @Column(name = "teacherid")
    private String teacherid;
    @Id
    @Column(name = "level")
    private String level;
    @Id
    @Column(name = "language")
    private String language;
    @OneToMany(mappedBy = "studygroupByFkLessonTeacherid")
    private Collection<LessonEntity> lessons;
    @OneToMany(mappedBy = "studygroupByLessonFkTeacherLevelLang")
    private Collection<LessonEntity> lessons_0;
    @ManyToOne
    @JoinColumn(name = "teacherid", referencedColumnName = "langschoolcardnumber", nullable = false, insertable = false, updatable = false)
    private PersonEntity personByTeacherid;
    @ManyToOne
    @JoinColumn(name = "teacherid", referencedColumnName = "langschoolcardnumber", nullable = false, insertable = false, updatable = false)
    private TeacherEntity teacherByTeacherid;
    @OneToMany(mappedBy = "studygroupByFkStudygroupcreationTeacherid")
    private Collection<StudygroupcreationEntity> studygroupcreations;
    @OneToMany(mappedBy = "studygroupByStudygroupcreationFkTeacherLevelLang")
    private Collection<StudygroupcreationEntity> studygroupcreations_0;

    public String getTeacherid() {
        return teacherid;
    }

    public void setTeacherid(String teacherid) {
        this.teacherid = teacherid;
    }

    public String getLevel() {
        return level;
    }

    public void setLevel(String level) {
        this.level = level;
    }

    public String getLanguage() {
        return language;
    }

    public void setLanguage(String language) {
        this.language = language;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        StudygroupEntity that = (StudygroupEntity) o;

        if (teacherid != null ? !teacherid.equals(that.teacherid) : that.teacherid != null) return false;
        if (level != null ? !level.equals(that.level) : that.level != null) return false;
        if (language != null ? !language.equals(that.language) : that.language != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = teacherid != null ? teacherid.hashCode() : 0;
        result = 31 * result + (level != null ? level.hashCode() : 0);
        result = 31 * result + (language != null ? language.hashCode() : 0);
        return result;
    }
}
