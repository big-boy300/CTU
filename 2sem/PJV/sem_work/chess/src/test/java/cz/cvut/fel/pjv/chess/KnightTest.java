/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.cvut.fel.pjv.chess;

import java.util.ArrayList;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author danilrom
 */
public class KnightTest {

    public KnightTest() {
    }

    @BeforeClass
    public static void setUpClass() {
        System.out.println("BC");
    }

    @AfterClass
    public static void tearDownClass() {
        System.out.println("AC");
    }

    @Before
    public void setUp() {
        System.out.println("B");
    }

    @After
    public void tearDown() {
        System.out.println("A");
    }

    /**
     * Test of createPossibleMoves method, of class Knight.
     */
    @Test
    public void testCreatePossibleMoves() {
        System.out.println("createPossibleMoves");
        ArrayList<Field> fields = new ArrayList<Field>(64);
        int xFrom = 0, yFrom = 0, xTo = 80, yTo = 80, pieceColor = 0, fieldColor = 1;
        for (int i = 0; i < 64; ++i) {
            Field field = new Field(xFrom, yFrom, xTo, yTo, pieceColor, fieldColor, i);
            xTo += 80;
            xFrom += 80;
            if (i != 0 && i % 7 == 0) {
                yFrom += 80;
                yTo += 80;
                xFrom = 0;
                xTo = 80;
            }
            if (i >= 0 && i < 16) {
                field.setIsFree(false);
                pieceColor = 0;
            } else if (i >= 48 && i < 64) {
                pieceColor = 1;
            } else {
                field.setIsFree(false);
                pieceColor = 2;
            }
            if (i % 2 != 0) {
                fieldColor = 0;
            } else {
                fieldColor = 1;
            }
            fields.add(field);
        }
        int index = 1;
        Knight instance = new Knight(0, 97, 7, "nb", 1);
        ArrayList<Field> expResult = new ArrayList<Field>();
        expResult.add(new Field(0, 80, 80, 160, 2, 1, 16));
        expResult.add(new Field(160, 80, 240, 160, 2, 1, 18));
        ArrayList<Field> result = instance.createPossibleMoves(fields, index);
        int counter = 0;
        for (Field f : result) {
            assertEquals(expResult.get(counter).getIndex(), result.get(counter).getIndex());
            counter++;
        }
    }

    /**
     * Test of createAttackMoves method, of class Knight.
     */
    @Test
    public void testCreateAttackMoves() {
        System.out.println("createAttackMoves");
        ArrayList<Field> fields = new ArrayList<Field>(64);
        int xFrom = 0, yFrom = 0, xTo = 80, yTo = 80, pieceColor = 0, fieldColor = 1;
        for (int i = 0; i < 64; ++i) {
            Field field = new Field(xFrom, yFrom, xTo, yTo, pieceColor, fieldColor, i);
            xTo += 80;
            xFrom += 80;
            if (i != 0 && i % 7 == 0) {
                yFrom += 80;
                yTo += 80;
                xFrom = 0;
                xTo = 80;
            }
            if (i >= 0 && i < 16) {
                field.setIsFree(false);
                pieceColor = 0;
            } else if (i >= 48 && i < 64) {
                pieceColor = 1;
            } else {
                field.setIsFree(false);
                pieceColor = 2;
            }
            if (i % 2 != 0) {
                fieldColor = 0;
            } else {
                fieldColor = 1;
            }
            fields.add(field);
        }
        int index = 1;
        Knight instance = new Knight(0, 97, 7, "nb", 1);
        ArrayList<Field> expResult = new ArrayList<Field>();
        ArrayList<Field> result = instance.createAttackMoves(fields, index);
        assertEquals(expResult.isEmpty(), result.isEmpty());
    }
}
