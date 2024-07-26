package com.n0n3m4.DIII4A.launcher;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Handler;
import android.preference.PreferenceManager;
import android.view.View;
import android.widget.Button;

import com.karin.idTech4Amm.R;
import com.karin.idTech4Amm.lib.ContextUtility;
import com.n0n3m4.DIII4A.GameLauncher;
import com.n0n3m4.q3e.Q3ELang;
import com.n0n3m4.q3e.karin.KStr;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;

public final class ChooseCommandRecordFunc extends GameLauncherFunc
{
    private String m_cmd;
    private String m_key;

    public ChooseCommandRecordFunc(GameLauncher gameLauncher, Runnable runnable)
    {
        super(gameLauncher, runnable);
    }

    public void Reset()
    {
    }

    public void Start(Bundle data)
    {
        super.Start(data);
        Reset();
        m_cmd = data.getString("command");
        m_key = data.getString("key");
        run();
    }

    public void run()
    {
        Set<String> records = PreferenceManager.getDefaultSharedPreferences(m_gameLauncher).getStringSet(m_key, new HashSet<>());

        final int size = records.size();
        final CharSequence[] items = new CharSequence[size];
        final String[] values = new String[size];
        final boolean[] selected = new boolean[size];
        final Set<String> result = new HashSet<>();

        int i = 0;
        for (String f : records)
        {
            items[i] = f;
            values[i] = f;
            selected[i] = f.equals(m_cmd);
            if(selected[i])
                result.add(f);
            i++;
        }

        final boolean AllowAdd = !records.contains(m_cmd);
        AlertDialog.Builder builder = new AlertDialog.Builder(m_gameLauncher);
        builder.setTitle(R.string.choose_command_record);
        builder.setMultiChoiceItems(items, selected, new DialogInterface.OnMultiChoiceClickListener()
        {
            @Override
            public void onClick(DialogInterface dialog, int which, boolean isChecked)
            {
                String cmd = values[which];
                if (isChecked)
                    result.add(cmd);
                else
                    result.remove(cmd);
                AlertDialog alert = (AlertDialog) dialog;
                Button button = alert.getButton(AlertDialog.BUTTON_NEUTRAL);
                if (AllowAdd)
                {
                    if(result.isEmpty())
                    {
                        button.setText(R.string.add);
                        button.setEnabled(true);
                    }
                    else
                    {
                        button.setText(R.string.edit);
                        button.setEnabled(result.size() == 1);
                    }
                }
                else
                    button.setEnabled(result.size() == 1);
                alert.getButton(AlertDialog.BUTTON_NEGATIVE).setEnabled(!result.isEmpty());
                alert.getButton(AlertDialog.BUTTON_POSITIVE).setEnabled(result.size() == 1);
            }
        }).setNegativeButton(R.string.remove, null);
        builder.setNeutralButton(AllowAdd ? R.string.add : R.string.edit, null);
        builder.setPositiveButton(R.string.choose, null);
        AlertDialog dialog = builder.create();
        dialog.setOnShowListener(new DialogInterface.OnShowListener()
        {
            @Override
            public void onShow(DialogInterface d)
            {
                dialog.getButton(AlertDialog.BUTTON_NEUTRAL).setOnClickListener(new View.OnClickListener() {
                    public void onClick(View view)
                    {
                        if(AllowAdd && result.isEmpty())
                        {
                            if(Add(m_cmd) > 0)
                            {
                                dialog.dismiss();
                                run();
                            }
                        }
                        else
                        {
                            if(result.size() != 1)
                            {
                                Toast_short(Q3ELang.tr(m_gameLauncher, R.string.must_choose_a_command));
                            }
                            else
                            {
                                dialog.dismiss();
                                Edit(result);
                            }
                        }
                    }
                });
                dialog.getButton(AlertDialog.BUTTON_NEGATIVE).setOnClickListener(new View.OnClickListener() {
                    public void onClick(View view)
                    {
                        if(Remove(result) > 0)
                        {
                            dialog.dismiss();
                            run();
                        }
                    }
                });
                dialog.getButton(AlertDialog.BUTTON_POSITIVE).setOnClickListener(new View.OnClickListener() {
                    public void onClick(View view)
                    {
                        String cmd = Choose(result);
                        if(null != cmd)
                        {
                            SetResult(cmd);
                            Callback();
                            dialog.dismiss();
                        }
                    }
                });

                Button button = dialog.getButton(AlertDialog.BUTTON_NEUTRAL);
                if (AllowAdd)
                {
                    if(result.isEmpty())
                    {
                        button.setText(R.string.add);
                        button.setEnabled(true);
                    }
                    else
                    {
                        button.setText(R.string.edit);
                        button.setEnabled(result.size() == 1);
                    }
                }
                else
                    button.setEnabled(result.size() == 1);
                dialog.getButton(AlertDialog.BUTTON_NEGATIVE).setEnabled(!result.isEmpty());
                dialog.getButton(AlertDialog.BUTTON_POSITIVE).setEnabled(result.size() == 1);
            }
        });
        dialog.show();
    }

    private int Add(String cmd)
    {
        if(KStr.IsBlank(cmd))
            return 0;
        SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(m_gameLauncher);
        Set<String> records = new LinkedHashSet<>(preferences.getStringSet(m_key, new HashSet<>()));
        if(records.contains(cmd))
            return 0;
        records.add(cmd);
        preferences.edit().putStringSet(m_key, records).commit();
        return 1;
    }

    private int Edit(Set<String> cmds)
    {
        if(cmds.size() != 1)
        {
            Toast_short(Q3ELang.tr(m_gameLauncher, R.string.must_choose_a_command));
            return 0;
        }
        final String cmd = cmds.iterator().next();
        String[] args = {""};
        boolean[] error = {false};
        m_cmd = cmd;
        AlertDialog input = ContextUtility.Input(m_gameLauncher, Q3ELang.tr(m_gameLauncher, R.string.edit_command_record), Q3ELang.tr(m_gameLauncher, R.string.command), cmd, args, new Runnable()
        {
            @Override
            public void run()
            {
                String arg = args[0];
                if (arg.isEmpty())
                {
                    error[0] = true;
                    Toast_short(Q3ELang.tr(m_gameLauncher, R.string.empty_content));
                }
                else if(!cmd.equals(arg))
                {
                    SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(m_gameLauncher);
                    List<String> records = new ArrayList<>(preferences.getStringSet(m_key, new HashSet<>()));
                    int i = records.indexOf(cmd);
                    if (i != -1)
                    {
                        records.remove(i);
                        if(records.contains(arg))
                        {
                            error[0] = true;
                            Toast_short(Q3ELang.tr(m_gameLauncher, R.string.command_exists));
                        }
                        else
                        {
                            m_cmd = arg;
                            records.add(i, arg);
                            preferences.edit().putStringSet(m_key, new LinkedHashSet<>(records)).commit();
                        }
                    }
                }
            }
        }, null, null, null);
        input.setOnDismissListener(new DialogInterface.OnDismissListener()
        {
            @Override
            public void onDismiss(DialogInterface dialog)
            {
                if(error[0])
                    new Handler().postDelayed(ChooseCommandRecordFunc.this, 200);
                else
                    run();
            }
        });
        return 1;
    }

    private int Remove(Set<String> cmds)
    {
        SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(m_gameLauncher);
        Set<String> records = new LinkedHashSet<>(preferences.getStringSet(m_key, new HashSet<>()));
        int res = 0;
        for (String cmd : cmds)
        {
            records.remove(cmd);
            res++;
        }
        preferences.edit().putStringSet(m_key, records).commit();
        return res;
    }

    private String Choose(Set<String> cmds)
    {
        if(cmds.size() != 1)
        {
            Toast_short(Q3ELang.tr(m_gameLauncher, R.string.must_choose_a_command));
            return null;
        }
        return cmds.iterator().next();
    }
}
